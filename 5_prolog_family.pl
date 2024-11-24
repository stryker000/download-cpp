% Family relationships
parent(john, mary).
parent(john, michael).
parent(mary, ann).
parent(michael, tom).

% Gender facts
male(john).
male(michael).
female(mary).
female(ann).
female(tom).

% Rules
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.
ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(Z, Y), ancestor(X, Z).
