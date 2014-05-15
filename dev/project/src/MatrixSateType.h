#pragma once

class MatrixSateType
{
public:
    enum Enum
    {
        Idle = 0,
        SearchForMatches,
        RemoveCells
        //TODO
    };

    static std::string toString(Enum e)
    {
        switch (e)
        {
        case MatrixSateType::Idle:
            return "Idle";
            break;
        case MatrixSateType::SearchForMatches:
            return "SearchForMatches";
            break;
        case MatrixSateType::RemoveCells:
            return "RemoveCells";
            break;
        default:
            return "UNKNOWN";
            assert(false);
            break;
        }
    }
};