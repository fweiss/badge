#include "Gravity.h"

#include <math.h>
#include <cmath>
#include <algorithm>
#include <random>

#include "esp_log.h"
const char* TAG = "Gravity";

Gravity::Gravity(Display &display) : Animation(display, 100) {
    this->motionData = { 0.0, 0.0, 0.0 };
    this->board = std::vector<std::vector<Cell*>>(8, std::vector<Cell*>(8, NULL));
    this->concaveBias = std::vector<std::vector<float>>(8, std::vector<float>(8, 0.0));
    for (int r=0; r<8; r++) {
        for (int c=0; c<8; c++) {
            // linear list of points
            CPoint cp;
            cp.r = r;
            cp.c = c;
            this->allPoints.push_back(cp);

            // concave bias
            float radius = sqrt((3.5 - r) * (3.5 - r) + (3.5 - c) * (3.5 - c));
            float bias = 0.0; //radius * 0.5;
            this->concaveBias[r][c] = bias;
        }
    }
    this->initBoardRandom();
}

Gravity::~Gravity() {
}

void Gravity::initBoardRandom() {
    std::vector<ZColor> colorPallette = {
        // { .comp = { 160, 160, 20, 255 } }
        { .flat = 0xa04040ff },
        { .flat = 0x40a040ff },
        { .flat = 0x4040a0ff },
        { .flat = 0xa0a040ff },
        { .flat = 0xa040a0ff }
    };

    std::vector<CPoint> cpoints = this->allPoints;

    // randomized points
    auto rng = std::default_random_engine {};
    std::shuffle(cpoints.begin(), cpoints.end(), rng);

    // sample and assign cell
    const uint16_t pieces = 13;  
    for (int x=0; x<pieces; x++) {
        CPoint cp = cpoints[x];
        ZColor acolor = colorPallette[x % colorPallette.size()];
        Cell* cell = new Cell(acolor);
        this->board[cp.r][cp.c] = cell;
    }
}

// the view, but we allow some processing here
// because to throttle it
// floating point, slow?
void Gravity::drawFrame() {
    // updateSimpleFrame();
    drawBoard();
    display.update();
}

void Gravity::drawBoard() {
    updateBoardMotion(this->motionData);
    display.clear();
    const int rows = 8;
    const int cols = 8;
    for (int r=0; r<rows; r++) {
        for (int c=0; c<cols; c++) {
            Cell* cell = this->board[r][c];
            if (cell) {
                this->paintPixel(r, c, cell->color);
            }
        }
    }
}

void Gravity::paintPixel(uint16_t row, uint16_t col, ZColor& color) {
    int offset = row * 8 + col;
    display.setPixel(offset, color.comp.r, color.comp.g, color.comp.b);

    // paths for each occupied point
    // projected on gradient 
}

// use board distance/gravity gradient
// to rearrange cells
void Gravity::updateBoardMotion(MotionData motionData) {
    // note sensor is rotated 180 around z
    float angle = atan2(motionData.ay, -motionData.ax);
    // ESP_LOGI(TAG, "angle %f", angle);

    std::vector<SourceChoices> moves;
    for (auto & pf : this->allPoints) {
        const bool picked = true; //pf.c == 4 && pf.r == 2; // debug single cell
        // only filled cells
        if (this->board[pf.r][pf.c] != NULL && picked) {
            std::vector<TargetCost> costs;
            for (auto & pe : this->allPoints) {
                // only unfilled cells
                if (this->board[pe.r][pe.c] == NULL) {
                    float bias = concaveBias[pe.r][pe.c];
                    const float dx = pe.c - pf.c;
                    const float dy = pe.r - pf.r;
                    const float ds = sqrt(dx * dx + dy * dy);
                    const float phi = atan2(dy, dx);
                    // consider not only the direct projection on the gradient
                    // but also the deviation of the direction
                    // take a penalty when the angles diverge too much
                    const float cost =  ds * cos(angle - phi) + bias;
                    // const float cost =  ds * cos(angle - phi) - 0.0 * abs(ds * sin(angle - phi));
                    // balloons (>) or marbles (<)
                    if (cost < 0.0) { // only the falling ones
                        costs.push_back({ pe, cost });
                    }
                }
            }
            // ensure only non-empty choices
            // note that comparision returns boolean, not -/+/0
            // descending since "down" becomes more negative
            if (costs.size() > 0) {
                const auto descending = [](TargetCost a, TargetCost b) { return a.cost > b.cost; };
                std::sort(costs.begin(), costs.end(), descending);

                SourceChoices move{ pf, costs };
                gentleDrop(move);
            }
        }
    }
}

void Gravity::gentleDrop(SourceChoices &move) {
    // gentle drop, try to slow down drops
    // note "down" is more negative
    const float dropLimit = -1.0;
    TargetCost* targetChoice = NULL;

    for (int i=0; i<move.choices.size(); i++) {
        TargetCost* choice = &move.choices[i];
        auto pe = choice->point;
        // limit how far to drop
        // try to pick not the nearest nor the farthest
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
        auto pf = move.point;
        auto pe = targetChoice->point;
        if (this->board[pe.r][pe.c] == NULL) {
            this->board[pe.r][pe.c] = this->board[pf.r][pf.c];
            this->board[pf.r][pf.c] = NULL;
        }
    }
}

void Gravity::setMotion(MotionData motionData) {
    this->motionData = motionData;
}
