# Squares

A simple starter animation on the theme of squares. It can draw various sized open and closed
squares over a background.

## Data structures

The basic structure is a frmae, implemented as set of indices to pixels. The particular matrix, CJMCU-8x8, has eight rows, each having
eight pixels number 0-7, 8-15, 16-31, etc. For example, a 3x3 square would be the indices 0, 1, 2, 8, 10, 16, 17, 18.

An animation is a list of frames.
