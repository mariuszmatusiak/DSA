#ifndef DSA_ADAPTER_H
#define DSA_ADAPTER_H

class Pizza {
protected:
    m_Name;
public:
    virtual ~Pizza() = default;
};

class PizzaDecorator : public Pizza {
public:
    explicit PizzaDecorator(const Pizza& pizzaRef)
protected:
    const Pizza* m_PizzaPtr;
}

#endif /* DSA_ADAPTER_H */
