#pragma once

class Block
{
public:
    Block() {}
    Block(unsigned int id) : m_ID(id) {}

    unsigned int GetID() const { return m_ID; }
    void SetID(unsigned int id) { m_ID = id; }

private:
    unsigned int m_ID = 0;
};