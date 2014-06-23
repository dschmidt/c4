#ifndef PATTERN_H
#define PATTERN_H

class Pattern
{
public:
    // Transformation matrix retrieval.
    double width;
    double centre[2];
    double trans[3][4];
    int found;
    int id;

    Pattern(double pattWidth = 80.0);
};

#endif // PATTERN_H
