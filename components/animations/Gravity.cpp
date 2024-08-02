#include "Gravity.h"

#include <math.h>
#include <cmath>
#include <algorithm>
#include <random>

#include "esp_log.h"
const char* TAG = "Gravity";

Gravity::Gravity() {
    this->motionData = { 0.0, 0.0, 0.0 };
    this->board = std::vector<std::vector<Cell*>>(8, std::vector<Cell*>(8, NULL));
    for (int r=0; r<8; r++) {
        for (int c=0; c<8; c++) {
            CPoint cp;
            cp.r =r;
            cp.c = c;
            this->allPoints.push_back(cp);
        }
    }
    this->initBoardRandom();
}


Gravity::~Gravity() {
}

// old
int b(float x) {
    if (x > 7) x = 7;
    if (x < 0) x = 0;
    return x;
}

// different than updateBoard
void Gravity::initBoard() {
    ZColor color{ 0xa04040ff };
    Cell* cell = new Cell(color);
    this->board[2][3] = cell;
}

void Gravity::initBoardRandom() {

    // try to get a uniform pallette with distinct colors
    // fixme yellow is not working
    std::vector<ZColor> colorPallette{
        ZColor(255, 0, 0),
        ZColor(0, 255, 0),
        ZColor(0, 0, 255),
        ZColor(255, 255, 255),
        ZColor(255, 255, 0),
    };

    std::vector<CPoint> cpoints = this->allPoints;

    // randomized points
    auto rng = std::default_random_engine {};
    std::shuffle(cpoints.begin(), cpoints.end(), rng);

    // sample and assign cell
    const uint16_t pieces = 23;  
    ESP_LOGI(TAG, "assigning pallette %d to pieces %d", colorPallette.size(), pieces);
    for (int x=0; x<pieces; x++) {
        CPoint cp = cpoints[x];
        ZColor acolor = colorPallette[x % colorPallette.size()];
        Cell* cell = new Cell(acolor);
        this->board[cp.r][cp.c] = cell;
    }

    const int rows = 8;
    const int cols = 8;
    for (int r=0; r<rows; r++) {
        for (int c=0; c<cols; c++) {
            Cell* cell = this->board[r][c];
            if (cell) {
                ESP_LOGI(TAG, "cell color %lx", cell->color.flat);
            }
        }
    }
}

// the view, but we allow some processing here
// because to throttle it
// floating point, slow?
void Gravity::drawFrame(Frame &frame) {
    updateBoardMotion(this->motionData);
    frame.clear();
    const int rows = 8;
    const int cols = 8;
    for (int r=0; r<rows; r++) {
        for (int c=0; c<cols; c++) {
            Cell* cell = this->board[r][c];
            if (cell) {
                int offset = r * 8 + c;
                frame.setPixel(offset, cell->color.flat);
            }
        }
    }
}

void Gravity::drawBoard() {
    // updateBoardMotion(this->motionData);
    // display.clear();
    // const int rows = 8;
    // const int cols = 8;
    // for (int r=0; r<rows; r++) {
    //     for (int c=0; c<cols; c++) {
    //         Cell* cell = this->board[r][c];
    //         if (cell) {
    //             this->paintPixel(r, c, cell->color);
    //         }
    //     }
    // }
}

void Gravity::paintPixel(uint16_t row, uint16_t col, ZColor& color) {
    // int offset = row * 8 + col;
    // display.setPixel(offset, color.comp.r, color.comp.g, color.comp.b);

    // paths for each occupied point
    // projected on gradient 
}

typedef struct {
    CPoint point;
    float cost;
} TargetCost;

typedef struct {
    CPoint point;
    std::vector<TargetCost> choices;
} SourceChoices;

static float pangle;

// use board distance/gravity gradient
// to rearrange cells
void Gravity::updateBoardMotion(MotionData motionData) {
    // adjust for
    float angle = atan2(motionData.ay, -motionData.ax);
    if (angle == pangle) {
        // optional optimize to avoid recalculation
        // but for slow drops, need to converge
        // return;
    }
    pangle = angle;
    // ESP_LOGI(TAG, "angle %f", angle);

    std::vector<SourceChoices> moves;
    for (auto & pf : this->allPoints) {
        const bool picked = true; //pf.c == 4 && pf.r == 2;
        if (this->board[pf.r][pf.c] != NULL && picked) {
            std::vector<TargetCost> costs;
            for (auto & pe : this->allPoints) {
                if (this->board[pe.r][pe.c] == NULL) {
                    const float dx = pe.c - pf.c;
                    const float dy = pe.r - pf.r;
                    const float ds = sqrt(dx * dx + dy * dy);
                    const float phi = atan2(dy, dx);
                    // consider not only the direct projection on the gradient
                    // but also the deviation of the direction
                    // take a penalty when the angles diverge too much
                    const float cost =  ds * cos(angle - phi);
                    // const float cost =  ds * cos(angle - phi) - 0.0 * abs(ds * sin(angle - phi));
                    // balloons (>) or marbles (<)
                    if (cost < 0.0) { // only the falling ones
                        costs.push_back({ pe, cost });
                    }
                }
            }
            // < note that comparision returns boolean, not -/+/0
            // delay sorting to motion algorithm
            // ensure only non-empty choices
            // descending since "down" becomes more negative
            if (costs.size() > 0) {
                const auto descending = [](TargetCost a, TargetCost b) { return a.cost > b.cost; };
                std::sort(costs.begin(), costs.end(), descending);
                moves.push_back({ pf, costs });
            }
        }
    }

    // pick the farthest drop for given source
    // const auto selectTarget = [](SourceChoices& move) -> TargetCost {
    //     TargetCost target;
    //     for ( auto & choice : move.choices) {
    //         auto pe = choice.point;
    //         if (this->board[pe.r][pe.c] == NULL) {
    //             this->board[pe.r][pe.c] = this->board[pf.r][pf.c];
    //             this->board[pf.r][pf.c] = NULL;
    //             break;
    //         }
    //     }
    //     return 
    // }

    // gentle drop
    // remeber "down" is more negative
    const float dropLimit = -1.0;
    for ( auto & frank : moves) {
        auto pf = frank.point;
        // try to slow down drops
        // why reverse the ascending?
        // std::reverse(frank.choices.begin(), frank.choices.end());
        TargetCost* targetChoice = NULL;
        for (int i=0; i<frank.choices.size(); i++) {
            TargetCost* choice = &frank.choices[i];
            auto pe = choice->point;
            // limit how far to drop
            // try to pick not the nearest nor th farthest
            if (this->board[pe.r][pe.c] == NULL) { // skip occupied targets
                if (choice->cost > dropLimit) {
                    targetChoice = choice;
                } else {
                    // fallback if none < dropLimit
                    if (targetChoice == NULL) {
                        targetChoice = choice;
                    }
                    break;
                }
            }
        }
        if (targetChoice != NULL) {
            auto pe = targetChoice->point;
            if (this->board[pe.r][pe.c] == NULL) {
                this->board[pe.r][pe.c] = this->board[pf.r][pf.c];
                this->board[pf.r][pf.c] = NULL;
            }
        }
    }

    // swap as per cost
    // for ( auto & frank : moves) {
    //     auto pf = frank.point;
    //     for ( auto & choice : frank.choices) {
    //         auto pe = choice.point;
    //         if (this->board[pe.r][pe.c] == NULL) {
    //             this->board[pe.r][pe.c] = this->board[pf.r][pf.c];
    //             this->board[pf.r][pf.c] = NULL;
    //             break;
    //         }
    //     }
    // }
}

void Gravity::updateSimpleFrame() {
    // display.clear();

    // debug verify addressing
    // int p = this->x + (8 * this->y);
    // display.setPixel(p, 10, 10, 160);
    // this->x = (this->x + 1) % 8;
    // if (this->x == 0) {
    //     this->y = (this->y + 1) % 8;
    // }

    const float ax = this->motionData.ax;
    const float ay = this->motionData.ay;

    // float r = sqrt(ax * ax + ay * ay);
    // float angle = atan2(this->motionData.ay, this->motionData.ax);
    // float r *= 4.2; // empirical to reach corners 
    // float dx = r * cos(angle);
    // float dy = r * - sin(angle); // top-down

    float r = 4.7;
    float dx = r * ax;
    float dy = r * - ay;

    int ox = b(3.5 + dx);
    int oy = b(3.5 + dy);
    printf("offsets %d, %d\n", ox, oy);

    int offset = ox + 8 * oy;
    if (offset > 63) {
        offset = 63;
    }
    // display.setPixel(offset, 160, 160, 10);
}

void Gravity::setMotion(MotionData motionData) {
    this->motionData = motionData;
}
