#include "Collider2D.h"
const std::string Collider2D::name = "Collider2D";

Collider2D::Collider2D(Object * _gameObject) : Component(_gameObject), size(1, 1), offset(0, 0)
{

}

