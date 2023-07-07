#include "Node.h"

Node::Node(std::string message) noexcept
	: message(std::move(message))
	, next(nullptr)
{
}

void Node::setNext(const std::shared_ptr<Node>& nextNode)
{
	this->next = nextNode;
}

std::shared_ptr<Node> Node::getNext() const
{
	return next;
}

std::string Node::getMessage() const
{
	return message;
}
