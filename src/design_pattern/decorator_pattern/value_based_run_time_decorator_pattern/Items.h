//
// Created by kang on 2024/11/11.
//

#ifndef CPP_TEST_PRICEDITEM_H
#define CPP_TEST_PRICEDITEM_H

#include "../../UseCase.h"

class Item
{
public:
    template<typename T>
    Item(T item) : pimpl_(std::make_unique<Model<T>>(std::move(item))) {}

    Item(Item const& item) : pimpl_(item.pimpl_->clone()) {}

    Item& operator=(Item const& item)
    {
        pimpl_ = item.pimpl_->clone();
        return *this;
    }

    ~Item() =default;
    Item(Item &&) = default;
    Item& operator=(Item&& item)=default;

    double price() const {return pimpl_->price();}

private:
    struct Concept
    {
        virtual ~Concept() = default;
        virtual double price() const =0;
        virtual std::unique_ptr<Concept> clone() const = 0;
    };

    template<typename T>
    struct Model : public Concept
    {
        explicit Model(T const& item): item_(item) {}
        explicit Model(T&& item) : item_(std::move(item)) {}

        double price() const override {return item_.price();}

        std::unique_ptr<Concept> clone() const override {
            return std::make_unique<Model<T>>(*this);
        }

        T item_;
    };

    std::unique_ptr<Concept> pimpl_;
};

#endif //CPP_TEST_PRICEDITEM_H
