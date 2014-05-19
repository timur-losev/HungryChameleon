#pragma once

class MatrixSateType
{
public:
    enum Enum
    {
        Idle = 0,
        SearchForMatches,
        Blink,
        RemoveCells,
        __Total
    };

    static std::string toString(Enum e)
    {
        switch (e)
        {
        case MatrixSateType::Idle:
            return "Idle";

        case MatrixSateType::SearchForMatches:
            return "SearchForMatches";

        case MatrixSateType::RemoveCells:
            return "RemoveCells";

        case MatrixSateType::Blink:
            return "Blink";

        default:
            return "UNKNOWN";
            assert(false);

        }
    }
};