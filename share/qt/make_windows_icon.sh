#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/tajcoin.ico

convert ../../src/qt/res/icons/tajcoin-16.png ../../src/qt/res/icons/tajcoin-32.png ../../src/qt/res/icons/tajcoin-48.png ${ICON_DST}
