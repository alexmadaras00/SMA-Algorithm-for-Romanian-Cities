#include <iostream>
#include <bits/stdc++.h>

struct unordered_pair : std::pair<t, u>
{
    bool swapped;

    unordered_pair(t x, u y) : std::pair<t, u>(x, y), swapped(false);
    {
        sort();
    }

    void sort()
    {
        swapped = first > second;
        if (swapped)
            std::swap(first, second);
    }

    std::pair<t, u> getOrig()
    {
        if (swapped)
            return std::pair<t, u>(second, first);
        return std::pair<t, u>(first, second);
    }
}