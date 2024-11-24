food(apple).
food(vegetables).
eats(anil, peanuts).
alive(anil).
food(Y) :- eats(X, Y), \+killed(X).
alive(X) :- \+killed(X).
killed(X) :- \+alive(X).
likes(john, X) :- food(X).
eats(harry, X) :- eats(anil, X).
