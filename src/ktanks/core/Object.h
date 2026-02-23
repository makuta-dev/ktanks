#ifndef KTANKS_OBJECT_H
#define KTANKS_OBJECT_H

#include <glm/vec2.hpp>

namespace ktanks {

    class Object {
    public:
        Object();
        Object(int id, const glm::vec2& pos, const glm::vec2& size);

        [[nodiscard]] int getID() const;
        [[nodiscard]] glm::vec2 getSize() const;
        [[nodiscard]] glm::vec2 getPos() const;

        void setID(int);
        void setSize(const glm::vec2&);
        void setPos(const glm::vec2&);

    private:
        int m_id;
        glm::vec2 m_pos;
        glm::vec2 m_size;
    };

}



#endif //KTANKS_OBJECT_H