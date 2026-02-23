#include "Object.h"

namespace ktanks {

    Object::Object() : m_id(-1), m_pos(0), m_size(0) {}

    Object::Object(int id, const glm::vec2& pos, const glm::vec2& size)
        : m_id(id), m_pos(pos), m_size(size) {}

    int Object::getID() const {
        return m_id;
    }

    glm::vec2 Object::getSize() const {
        return m_size;
    }

    glm::vec2 Object::getPos() const {
        return m_pos;
    }

    void Object::setID(const int id) {
        m_id = id;
    }

    void Object::setSize(const glm::vec2& s) {
        m_size = s;
    }

    void Object::setPos(const glm::vec2& p) {
        m_pos = p;
    }

}