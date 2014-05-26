#pragma once

class MatrixStateType
{
public:
    enum Enum
    {
        Idle = 0,
        SearchForMatches,
        Blink,
        RemoveCellAndGiveReward,
        FillCells,
        __Total
    };

    static std::string toString(Enum e)
    {
        switch (e)
        {
        case MatrixStateType::Idle:
            return "Idle";

        case MatrixStateType::SearchForMatches:
            return "SearchForMatches";

        case MatrixStateType::Blink:
            return "Blink";

        case MatrixStateType::RemoveCellAndGiveReward:
            return "RemoveCellAndGiveReward";

        case MatrixStateType::FillCells:
            return "FillCells";

        default:
            return "UNKNOWN";
            assert(false);

        }
    }
};