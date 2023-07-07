#pragma once
#include <memory>
#include <string>

class Node final
{
public:
	Node() = delete;
	Node(const Node& node) = delete;
	Node(Node&& node) = default;
	~Node() = default;
	Node& operator= (const Node& node) = delete;
	Node& operator= (Node&& node) = delete;

	explicit Node(std::string message) noexcept;

	void setNext(const std::shared_ptr<Node>& nextNode);
	[[nodiscard]] std::shared_ptr<Node> getNext() const;
	[[nodiscard]] std::string getMessage() const;
private:
	std::string message;
	std::shared_ptr<Node> next;
};

