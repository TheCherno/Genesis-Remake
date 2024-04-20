#include "Entity.h"

namespace Genesis {

    void Entity::OnInit(Level* level)
    {
        m_Level = level;
    }

    void Entity::Remove()
    {
        m_Level->Remove(this);
    }
} // Genesis