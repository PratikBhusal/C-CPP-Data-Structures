#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <initializer_list>
#include <iostream>
#include <istream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

template <typename T>
class BinarySearchTree
{// {{{
public: // {{{

    // Constructors {{{
    BinarySearchTree() = default;
    explicit BinarySearchTree(const T& root_val)
        : root( std::make_shared<Node>(root_val) ) {}
    BinarySearchTree(const std::initializer_list<T>& list) {
        for (const T& i : list) {
            this->insert(i);
        }
    }
    // Constructors }}}

    virtual ~BinarySearchTree() { delete_tree(root); }

    // (Deep) Copy Constrctor
    BinarySearchTree(const BinarySearchTree& other)
        { *this = other; }

    // (Deep) Copy Assignment Operator
    BinarySearchTree& operator=(const BinarySearchTree& other) {// {{{
        if (this != &other) {
            this->~BinarySearchTree();
            this->root = (other.root)
                ? std::make_shared<Node>(other.root->data)
                : nullptr;
            copy_tree(this->root, other.root);
        }
        return *this;
    }// }}}

    // Move Constructor
    BinarySearchTree(BinarySearchTree&& other) noexcept
        { *this = std::move(other); }

    // Move Assignment Operator
    BinarySearchTree<T>& operator=(BinarySearchTree<T>&& other) noexcept {// {{{
        if (this != &other) {
            this->~BinarySearchTree();
            root = std::move(other.root);
        }
        return *this;
    }// }}}

    virtual bool insert(const T& val);
    bool remove(const T& val) { return remove(val, root); }
    bool contains(const T& val) { return (get_node(val, root) != nullptr); }
    const T& get_min() const { return get_min_node(root)->data; }
    const T& get_max() const { return get_max_node(root)->data; }
    std::string to_string() const { return ("[" + to_string(root) + " ]"); }

    friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& obj) {
        os << obj.to_string();
        return os;
    }

// }}}

protected: // {{{

    class Node {
    public:// {{{
        T data;
        std::shared_ptr<Node> parent;
        std::shared_ptr<Node> left   = nullptr;
        std::shared_ptr<Node> right  = nullptr;

        explicit Node(const T& d, const std::shared_ptr<Node>& p = nullptr)
            : data(d), parent(p) {}

        virtual ~Node() {
            this->parent = nullptr;
            this->left   = nullptr;
            this->right  = nullptr;
            std::cout << "Deleting node with value: " << data
                      << " and address: " << this << std::endl;
        }

        Node(const Node& other)       = delete;
        Node& operator=(Node& other)  = delete;
        Node(Node&& other)            = delete;
        Node& operator=(Node&& other) = delete;

        Node& operator=(std::shared_ptr<Node>&& other) noexcept {// {{{
            if ( this->left && this->right && this != other->parent.get() ) {
                other->transplant(other->right);
                other->right         = this->right;
                other->right->parent = other;
            }

            if (!this->parent && other) {
                other->parent = nullptr;
            }
            else if (this->parent) {
                this->transplant(other);
            }

            if (this->left && this->right && other) {
                other->left         = this->left;
                other->left->parent = other;
            }

            return *this;
        }// }}}

        // Less than (<) Operator Overloading {{{
        friend bool operator<(const std::shared_ptr<Node>& lhs, const T& rhs) {
            return (lhs->data < rhs);
        }
        friend bool operator<(const T& lhs, const std::shared_ptr<Node>& rhs) {
            return (lhs < rhs->data);
        }
        friend bool operator<(const std::shared_ptr<Node>& lhs,
                              const std::shared_ptr<Node>& rhs) {
            return (lhs->data < rhs->data);
        }
        // Less than (<) Operator Overloading }}}

        // Greater than (>) Operator Overloading {{{
        friend bool operator>(const std::shared_ptr<Node>& lhs, const T& rhs) {
            return (rhs < lhs);
        }
        friend bool operator>(const T& lhs, const std::shared_ptr<Node>& rhs) {
            return (rhs < lhs);
        }
        friend bool operator>(const std::shared_ptr<Node>& lhs,
                              const std::shared_ptr<Node>& rhs) {
            return (rhs < lhs);
        }
        // Less than (<) Operator Overloading }}}

        // Less than or equal (<=) Operator Overloading {{{
        friend bool operator<=(const std::shared_ptr<Node>& lhs, const T& rhs) {
            return !(lhs > rhs);
        }
        friend bool operator<=(const T& lhs, const std::shared_ptr<Node>& rhs) {
            return !(lhs > rhs);
        }
        friend bool operator<=(const std::shared_ptr<Node>& lhs,
                               const std::shared_ptr<Node>& rhs) {
            return !(lhs > rhs);
        }
        // Less than or equal (<=) Operator Overloading }}}

        // Greater than or equal (<=) Operator Overloading {{{
        friend bool operator>=(const std::shared_ptr<Node>& lhs, const T& rhs) {
            return !(lhs < rhs);
        }
        friend bool operator>=(const T& lhs, const std::shared_ptr<Node>& rhs) {
            return !(lhs < rhs);
        }
        friend bool operator>=(const std::shared_ptr<Node>& lhs,
                               const std::shared_ptr<Node>& rhs) {
            return !(lhs < rhs);
        }
        // Greater than or equal (<=) Operator Overloading }}}

        // Equality (==) Operator Overloading {{{
        friend bool operator==(const std::shared_ptr<Node>& lhs, const T& rhs) {
            return (lhs->data == rhs);
        }
        friend bool operator==(const T& lhs, const std::shared_ptr<Node>& rhs) {
            return (lhs == rhs.data);
        }
        // Equality (==) Operator Overloading }}}

        // Inequality (!=) Operator Overloading {{{
        friend bool operator!=(const std::shared_ptr<Node>& lhs, const T& rhs) {
            return !(lhs == rhs);
        }
        friend bool operator!=(const T& lhs, const std::shared_ptr<Node>& rhs) {
            return !(lhs == rhs);
        }
        // Inquality (!=) Operator Overloading }}}

    // }}}
    protected: // {{{
        void transplant(std::shared_ptr<Node>& other) {
            if ( this != other.get() ) {
                if (this->parent->left.get() == this) {
                    this->parent->left = other;
                }
                else {
                    this->parent->right = other;
                }

                if (other) {
                    other->parent = this->parent;
                }
            }
        }

    // }}}
    };
    std::shared_ptr<Node> root = nullptr;

    virtual const std::string to_string(const std::shared_ptr<Node>& current) const;
    const std::shared_ptr<Node> get_node(const T& val, const std::shared_ptr<Node>& start) const;
    const std::shared_ptr<Node> get_min_node(const std::shared_ptr<Node>& start) const;
    const std::shared_ptr<Node> get_max_node(const std::shared_ptr<Node>& start) const;
    virtual bool remove(const T& val, const std::shared_ptr<Node>& start);
    virtual void copy_tree(std::shared_ptr<Node>& self, const std::shared_ptr<Node>& other);
    virtual void delete_tree(std::shared_ptr<Node>& current);

// }}}

};// }}}

template <typename T>
void BinarySearchTree<T>::copy_tree(std::shared_ptr<Node>& self,
                                    const std::shared_ptr<Node>& other)
{// {{{
    if (other) {
        self->left  = (other->left)
            ? std::make_shared<Node>(other->left->data, self)
            : nullptr;
        self->right = (other->right)
            ? std::make_shared<Node>(other->right->data, self)
            : nullptr;

        copy_tree(self->left, other->left);
        copy_tree(self->right, other->right);
    }
}// }}}

template <typename T>
void BinarySearchTree<T>::delete_tree(std::shared_ptr<Node>& current)
{// {{{
    if (current) {
        delete_tree(current->left);
        delete_tree(current->right);
        remove(current->data, current);
    }
}// }}}

template <typename T>
bool BinarySearchTree<T>::insert(const T& val)
{// {{{
    bool inserted = true;

    try {// {{{
        if (!root) {
            root = std::make_shared<Node>(val);
        }
        else {
            std::shared_ptr<Node> prev = nullptr;
            std::shared_ptr<Node> temp = root;

            while (temp) {
                prev = temp;

                if (temp == val) {
                    throw std::invalid_argument("Item \"" + std::to_string(val)
                        + "\" already exists in the tree.");
                }

                temp = (temp < val) ? temp->right : temp->left;
            }

            if (prev < val) {
                prev->right = std::make_shared<Node>(val, prev);
            }
            else {
                prev->left = std::make_shared<Node>(val, prev);
            }
            // std::cout << "prev value: " << prev->data << std::endl;
            // std::cout << "prev use count: " << prev.use_count()-1 << std::endl;
            // std::cout << "chid value: " << val << std::endl;
            // std::cout << "child use count: "
            //           << ( (prev < val) ? prev->right.use_count() : prev->left.use_count() )
            //           << std::endl;
            // std::cout << std::endl;
        }
    }// }}}
    catch(const std::bad_alloc& e) {
        std::cerr << "Allocation Failed: " << e.what() << std::endl;
        inserted = false;
    }
    catch(const std::invalid_argument& e) {
        std::cerr << "Invalid Argument: " << e.what() << std::endl;
        inserted = false;
    }
    catch(...) {
        std::cerr << "Something went wrong when inserting " << val << std::endl;
        inserted = false;
        exit(1);
    }


    return inserted;
}// }}}

template <typename T>
bool BinarySearchTree<T>::remove(const T& val,
                                 const std::shared_ptr<Node>& start)
{// {{{
    bool removed = true;

    try {// {{{
        std::shared_ptr<Node> deleting = get_node(val, start);

        if (!deleting) {
            throw std::invalid_argument("The parameter does not exist in the tree: ");
        }

        std::shared_ptr<Node> replacement =
            (!deleting->left && !deleting->right)
            ? nullptr
            : (!deleting->left)
                ? deleting->right
                : (!deleting->right)
                    ? deleting->left
                    : get_min_node(deleting->right);

        *deleting = std::move(replacement);
        if (root == deleting) {
            root = replacement;
        }

        // if (deleting) {// {{{
        //     std::cout << "deleting address: " << deleting << std::endl;
        //     std::cout << "deleting value: " << deleting->data << std::endl;

        //     std::cout << "deleting parent: " << deleting->parent << std::endl;
        //     std::cout << "deleting parent value: "
        //               << (deleting->parent ? std::to_string(deleting->parent->data) : "N/A")
        //               << std::endl;
        //     std::cout << "deleting left child: " << deleting->left << std::endl;
        //     std::cout << "deleting left child value: "
        //               << (deleting->left ? std::to_string(deleting->left->data) : "N/A")
        //               << std::endl;
        //     std::cout << "deleting right child: " << deleting->right << std::endl;
        //     std::cout << "deleting right child value: "
        //               << (deleting->right ? std::to_string(deleting->right->data) : "N/A")
        //               << std::endl;

        //     std::cout << "deleting left child's parent: "
        //               << (deleting->left ? deleting->left->parent : nullptr )<< std::endl;
        //     std::cout << "deleting left child's parent value: "
        //               << (deleting->left ? deleting->left->parent ? std::to_string(deleting->left->parent->data) : "N/A" : "N/A")
        //               << std::endl;
        //     std::cout << "deleting right child's parent: "
        //               << (deleting->right ? deleting->right->parent : nullptr )<< std::endl;
        //     std::cout << "deleting right child's parent value: "
        //               << (deleting->right ? deleting->right->parent ? std::to_string(deleting->right->parent->data) : "N/A" : "N/A")
        //               << std::endl;

        //     std::cout << std::endl;
        // }
        // else {
        //     std::cout << "deleting is nullptr" << std::endl << std::endl;
        // }

        // if (replacement) {
        //     std::cout << "replacement value: " << replacement->data << std::endl;

        //     std::cout << "replacement parent: " << replacement->parent << std::endl;
        //     std::cout << "replacement parent value: "
        //               << (replacement->parent ? std::to_string(replacement->parent->data) : "N/A")
        //               << std::endl;
        //     std::cout << "replacement left child: " << replacement->left << std::endl;
        //     std::cout << "replacement left child value: "
        //               << (replacement->left ? std::to_string(replacement->left->data) : "N/A")
        //               << std::endl;
        //     std::cout << "replacement right child: " << replacement->right << std::endl;
        //     std::cout << "replacement right child value: "
        //               << (replacement->right ? std::to_string(replacement->right->data) : "N/A")
        //               << std::endl;
        //     std::cout << "replacement left child's parent: "
        //               << (replacement->left ? replacement->left->parent : nullptr )<< std::endl;
        //     std::cout << "replacement left child's parent value: "
        //               << (replacement->left ? replacement->left->parent ? std::to_string(replacement->left->parent->data) : "N/A" : "N/A")
        //               << std::endl;
        //     std::cout << "replacement right child's parent: "
        //               << (replacement->right ? replacement->right->parent : nullptr )<< std::endl;
        //     std::cout << "replacement right child's parent value: "
        //               << (replacement->right ? replacement->right->parent ? std::to_string(replacement->right->parent->data) : "N/A" : "N/A")
        //               << std::endl;

        //     std::cout << std::endl;
        // }
        // else {
        //     std::cout << "replacement is nullptr" << std::endl << std::endl;
        // }// }}}
    }// }}}
    catch(const std::invalid_argument& e) {
        std::cerr << "Invalid Argument: " << e.what() << val <<  std::endl;
        removed = false;
    }
    catch(...) {
        std::cerr << "Something went wrong when deleting " << val << std::endl;
        removed = false;
        exit(1);
    }


    return removed;
}// }}}

template <typename T>
const std::shared_ptr<typename BinarySearchTree<T>::Node>
BinarySearchTree<T>::get_node(const T& val,
                              const std::shared_ptr<Node>& start) const
{// {{{
    std::shared_ptr<Node> current = start;

    while (current && current != val) {
        current = (current < val) ? current->right : current->left;
    }

    return current;
}// }}}

template <typename T>
const std::shared_ptr<typename BinarySearchTree<T>::Node>
BinarySearchTree<T>::get_min_node(const std::shared_ptr<Node>& start) const
{// {{{
    try {
        if (!start) {
            throw std::invalid_argument("Starting node is null.");
        }
    }catch(const std::invalid_argument& e) {
        std::cerr << "Invalid Arugment: " << e.what() << std::endl;
        exit(1);
    }

    std::shared_ptr<Node> curr = start;

    while (curr->left) {
        curr = curr->left;
    }

    return curr;
}// }}}

template <typename T>
const std::shared_ptr<typename BinarySearchTree<T>::Node>
BinarySearchTree<T>::get_max_node(const std::shared_ptr<Node>& start) const
{// {{{
    try {
        if (!start) {
            throw std::invalid_argument("Starting node is null.");
        }
    }catch(const std::invalid_argument& e) {
        std::cerr << "Invalid Arugment: " << e.what() << std::endl;
        exit(1);
    }

    std::shared_ptr<Node> curr = start;

    while (curr->right) {
        curr = curr->right;
    }

    return curr;
}// }}}

template <typename T>
const std::string BinarySearchTree<T>::to_string(const std::shared_ptr<Node>& current) const
{// {{{
    std::string str;

    if (current) {
        str += to_string(current->left);
        str += " " + std::to_string(current->data);
        str += to_string(current->right);
    }

    return str;
}// }}}
#endif /* BINARYSEARCHTREE_HPP */
