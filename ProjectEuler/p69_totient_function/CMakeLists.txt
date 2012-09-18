CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (TotientRatio)

ADD_LIBRARY (TotientLib TotientFunction.cpp)
ADD_EXECUTABLE (TotientRatio TotientRatioMain.cpp)
TARGET_LINK_LIBRARIES (TotientRatio TotientLib)
