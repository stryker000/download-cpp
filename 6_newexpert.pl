car(sedan).
car(suv).
car(hatchback).
car(truck).
car(sports_car).

purpose(family).
purpose(road_trip).
purpose(off_road).
purpose(speed).
purpose(cargo).

fuel_type(petrol).
fuel_type(diesel).
fuel_type(electric).
fuel_type(hybrid).

recommend_car(Car) :-
    write('What is the purpose of the car? (family, road_trip, off_road, speed, cargo): '),
    read(Purpose),
    suitable_car(Car, Purpose).

suitable_car(sedan, family) :- 
    write('We recommend a Sedan for family purposes.'), nl.
suitable_car(suv, road_trip) :- 
    write('We recommend an SUV for road trips.'), nl.
suitable_car(truck, cargo) :- 
    write('We recommend a Truck for transporting cargo.'), nl.
suitable_car(sports_car, speed) :- 
    write('We recommend a Sports Car for speed enthusiasts.'), nl.
suitable_car(suv, off_road) :- 
    write('We recommend an SUV for off-road adventures.'), nl.

should_sell :-
    write('Is the car old? (yes/no): '),
    read(Old),
    write('Are you unsatisfied with the current performance? (yes/no): '),
    read(Performance),
    suggest_selling(Old, Performance).

suggest_selling(yes, yes) :- 
    write('You should consider selling your car.'), nl.
suggest_selling(no, _) :- 
    write('You should keep your car for now.'), nl.
suggest_selling(_, no) :- 
    write('You should keep your car if you are satisfied with its performance.'), nl.

start :-
    write('Welcome to the Car Expert System'), nl,
    write('Would you like a car recommendation or sell advice? (recommend/sell): '),
    read(Choice),
    handle_choice(Choice).

handle_choice(recommend) :- recommend_car(_).
handle_choice(sell) :- should_sell.
handle_choice(_) :- write('Invalid choice, please try again.'), nl, start.
