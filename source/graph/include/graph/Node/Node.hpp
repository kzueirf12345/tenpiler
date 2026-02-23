#pragma once

#include <memory>
#include <string>
#include <vector>
#include <concepts>

#include "graph/Node/OpsDumb.hpp"
#include "graph/Node/NodeMeta.hpp"

namespace tenpiler {
namespace graph {

template <typename T>
concept IsTenpilerNode = requires(T node) {
    { node.meta() } noexcept -> std::convertible_to<const NodeMeta&>;
};


class Node {
    
private:

    struct Concept {
        virtual ~Concept() = default;

        virtual const std::string&              getName   () const noexcept = 0;
        virtual const std::vector<std::string>& getInputs () const noexcept = 0;
        virtual const std::vector<std::string>& getOutputs() const noexcept = 0;

        virtual std::string_view getDot() const = 0;

        virtual std::unique_ptr<Concept> clone() const = 0;
    };

    template <typename T>
    struct Model : Concept {

        T node_instance;

        explicit Model(const T  &node) : node_instance(node)            {}
        explicit Model(      T &&node) : node_instance(std::move(node)) {}

        [[nodiscard]] std::unique_ptr<Concept> clone() const override {
            return std::make_unique<Model<T>>(*this);
        }

        [[nodiscard]] const std::string&              getName    () const noexcept override { return node_instance.meta().op_type; }
        [[nodiscard]] const std::vector<std::string>& getInputs  () const noexcept override { return node_instance.meta().inputs;  }
        [[nodiscard]] const std::vector<std::string>& getOutputs () const noexcept override { return node_instance.meta().outputs; }

        std::string_view getDot() const override {
            return dump::GetDot(node_instance);
        }
    };

private:

    std::unique_ptr<Concept> pImpl;

public:

    template <IsTenpilerNode T> 
    Node(T node)            : pImpl(std::make_unique<Model<T>>(std::move(node))) {}

    Node(const Node& other) : pImpl(other.pImpl->clone()) {}
    
    Node(Node&&)            noexcept = default;
    Node& operator=(Node&&) noexcept = default;

    Node& operator=(const Node& other) {
        if (this != &other) {
            pImpl = other.pImpl->clone();
        }
        return *this;
    }

    ~Node() = default;

public:

    [[nodiscard]] const std::string&              sayMyName () const noexcept { return pImpl->getName   (); }
    [[nodiscard]] const std::vector<std::string>& getInputs () const noexcept { return pImpl->getInputs (); }
    [[nodiscard]] const std::vector<std::string>& getOutputs() const noexcept { return pImpl->getOutputs(); }
    
    std::string_view getDot() const { return pImpl->getDot(); }
};

}

}