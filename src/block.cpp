#include "block.h"

Block::Block(Vector2 position)
{
    this -> position = position;
}

void Block::Draw()
{
    DrawRectangle(position.x,position.y, 3, 3, {243, 216, 63, 255} );
}

Rectangle Block::GetRect()
{
    return {position.x, position.y , 3, 3};
}
