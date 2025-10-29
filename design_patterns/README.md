# Design Patterns

## Adapter

### Object Adapter
A wrapper for legacy component, deriving another non-compatible base class. Uses composition for storing legacy component object and call its functions.

### Class Adapter
As above, except instead of composition it uses multiple inheritence, and inherit both legacy class (private inheritence) and non-compatible new base class (public inheritence).

## Bridge
For inheritence explosion problem. Instead of multiple inheritence to different classes, one base class has a composition to another base class, e.g. Element has a Style. Switching from inheritence to composition. E.g. IVehicle has IEngine

## Composite

## Decorator

## Facade

## Flyweight

## Proxy
