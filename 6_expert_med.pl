% Define diseases based on symptoms
disease(malaria) :- symptom(fever), symptom(headache), symptom(nausea).
disease(covid) :- symptom(fever), symptom(cough), symptom(fatigue).

% Predicate to ask yes/no questions about symptoms
ask_symptom(Symptom) :-
    format('Do you have ~w? (yes/no) ', [Symptom]),
    read(Response),
    (Response == yes -> assert(symptom(Symptom));
    Response == no -> true;
    write('Please answer yes or no.'), nl, ask_symptom(Symptom)).

% Collect symptoms based on user responses
get_symptoms :-
    ask_symptom(fever),
    ask_symptom(cough),
    ask_symptom(headache),
    ask_symptom(nausea),
    ask_symptom(fatigue).

% Predicate to predict disease based on symptoms
predict_disease :-
    findall(Disease, disease(Disease), Diseases),
    (member(malaria, Diseases) -> write('Possible disease: Malaria'), nl
    ; member(covid, Diseases) -> write('Possible disease: COVID-19'), nl
    ; write('No matching disease found for the provided symptoms.'), nl).

% To start the prediction
start :-
    get_symptoms,
    predict_disease.
