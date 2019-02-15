#ifndef SAMAI_HPP
#define SAMAI_HPP

#include <iostream>
#include "OthelloAI.hpp"
#include "OthelloGameState.hpp"
#include "OthelloBoard.hpp"
namespace huanjial
{

class SamAI: public OthelloAI

{
public:
    virtual std::pair<int, int> chooseMove(const OthelloGameState& state);

    int search(OthelloGameState& s, int depth); //Why the state is not a reference??

    void determine_color(const OthelloGameState& state);

    std::vector<std::pair<int, int>> get_available_move(const OthelloGameState& state);

    int eval_score(OthelloGameState& state);
   

private:
    char my_color;



};




}


#endif








