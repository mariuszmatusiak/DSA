# == Design Patterns ==

## 1. Adapter

### Object Adapter
A wrapper for a legacy component, deriving another non-compatible base class. Uses composition for storing legacy component object and call its functions.

### Class Adapter
As above, except for instead of the composition it uses multiple inheritence, and inherit both legacy class (private inheritence) and non-compatible new base class (public inheritence).

### Pros and cons
\- The additional class needs to be defined

![The Adapter Design Pattern](./img/adapter_block_scheme.png "The Adapter")

Image source: [\[1\]][1]

---

## 2. Bridge

- For inheritence explosion problem. 
- Instead of multiple inheritence of different classes, one base class has a composition to another base class
- Example: instead of BlackElement->Element, WhiteElement->Element, there is Element class which has a Style class composition. 
- Switching from inheritence to composition. E.g. IVehicle interface has IEngine (Electric Engine, Combustion Engine, etc.) interface
- Good for interfaces.

Image source: [\[1\]][1]

---

## 3. Composite

- A pattern typical for a file system
- Consists of composite (storing other composites) and leaf

Source: [\[1\]][1]

## Decorator

+ Adds new methods and data members without changing interface
+ Hides the wrapped object
+ alters design of an object by wrapping it and adding new functionality without changing the interface
- large number of small classes for numerous decorators
+ Examples: Desktop Computer with Graphics Card and Laptop Computer with Expanded Memory; Margherita Pizza with Spinach Toppings

Source: [\[1\]][1]

## Facade

+ wraps/encapsulates complex system and provides simple interface
+ similar to API gateway
- should follow the single-functionality rule
- should not expose internal subsystem types

Source: [\[1\]][1]

## Flyweight (pyłek)

+ used for memory reduction if multiple objects share the same information (intrinsic)
+ e.g. tree renderer, each tree sprite has coordinates and size (extrinsic state) but shares the same texture (intrinsic)
- increased complexity

Source: [\[1\]][1]

## Proxy

+ placeholder for another object
+ for lazy loading, caching, access control
+ 3 types:
  > virtual - postpones creating objects until they are needed being a lightweight placeholder
  > remote - local placeholder to control and optimize access to remote resources, hides details of network communication
  > protective - add restrictions for controlled access, authenticates user
- increased complexity and latency
- 

Source: [\[1\]][1]

# Useful links
1. [C++ Design Patterns: Structural]([1])

[1]: <https://www.linkedin.com/learning-login/share?forceAccount=false&redirect=https%3A%2F%2Fwww.linkedin.com%2Flearning%2Fc-plus-plus-design-patterns-structural-22183029%3Ftrk%3Dshare_ent_url%26shareId%3Dv9jpEbquS3y9vkLq92%252FrEg%253D%253D> "C++ Design Patterns: Structural"
