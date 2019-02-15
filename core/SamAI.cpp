#include <ics46/factory/DynamicFactory.hpp>
#include "SamAI.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, huanjial::SamAI, "Do It In One Line(Required)")

std::pair<int, int> huanjial::SamAI::chooseMove(const OthelloGameState& state)
{
    determine_color(state);

    std::vector<std::pair<int, int>> v = get_available_move(state);
    std::vector<int> compare_v;
    for (int i = 0; i < v.size(); ++i)
        {
            std::unique_ptr<OthelloGameState> c = state.clone();
            c -> makeMove(v[i].first, v[i].second);
            int result = search(*c, 3);
            compare_v.push_back(result);
        }
    int max_index = 0;
    for (int i = 0; i < compare_v.size(); ++i)
        {
        if (compare_v[i] > compare_v[max_index])
            max_index = i;
        }
    return v[max_index];
}


int huanjial::SamAI::search(OthelloGameState& s, int depth)
{
    if (depth == 0)
        {
        return eval_score(s);
        }
    else
        {
            std::vector<int> compare_v;
            std::vector<std::pair<int, int>> v = get_available_move(s);
            if (v.size() == 0) //There is no valid move for the next recursion.
                return eval_score(s);
            else
                {
                for (int i = 0; i < v.size(); ++i)
                    {
                    std::unique_ptr<OthelloGameState> c = s.clone();
                    c->makeMove(v[i].first,v[i].second);
                    int result = (*c, depth -1);
                    compare_v.push_back(result);
                    }
                if ((SamAI::my_color == 'B' && s.isBlackTurn() == true)||(SamAI::my_color == 'W' && s.isWhiteTurn()==true)) // is my if statement correct written in this way?
                    {
                    int max = compare_v[0];
                    for (int i = 0; i < compare_v.size(); ++i)
                        {
                        if (compare_v[i] > max)
                            max = compare_v[i];
                        }
                    return max;
                    }
                else
                    {
                    int min = compare_v[0];
                    for (int i = 0; i< compare_v.size(); ++i)
                        {
                        if (compare_v[i] < min)
                            min = compare_v[i];
                        }
                    return min;
                    }
                }
        }
}


int huanjial::SamAI::eval_score(OthelloGameState& state)
{
    int b_score = state.blackScore();
    int w_score = state.whiteScore();
    if (huanjial::SamAI::my_color == 'B')
        {
        return (b_score - w_score);
        }
    else if (huanjial::SamAI::my_color == 'W')
        {
        return (w_score - b_score);
        }
}



void huanjial::SamAI::determine_color(const OthelloGameState& state)
{ 
    if (state.isBlackTurn() == true)
        {
        huanjial::SamAI::my_color = 'B';
        }

    if (state.isWhiteTurn() == true)
        {
        huanjial::SamAI::my_color = 'W';
        }
}

std::vector<std::pair<int, int>> huanjial::SamAI::get_available_move(const OthelloGameState& state)
{
    std::vector<std::pair<int, int>> v;

    int w = state.board().width();
    int h = state.board().height();

    for (int x = 0; x < w; ++x) // x cordinate
        {
        for (int y = 0; y < h; ++y) // y cordinate
            {
            if (state.isValidMove(x,y) == true)
                {
                    std::pair<int,int> p = std::make_pair(x,y);
                    v.push_back(p);
                }
            }
        }
    return v;
}

    
