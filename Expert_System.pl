% Define facts about diseases and their symptoms
disease(flu).
disease(cold).
disease(allergy).
disease(covid19).

% Symptoms associated with each disease
symptom(flu, fever).
symptom(flu, cough).
symptom(flu, headache).
symptom(flu, body_ache).

symptom(cold, cough).
symptom(cold, runny_nose).
symptom(cold, sore_throat).
symptom(cold, headache).

symptom(allergy, sneezing).
symptom(allergy, itchy_eyes).
symptom(allergy, runny_nose).

symptom(covid19, fever).
symptom(covid19, cough).
symptom(covid19, fatigue).
symptom(covid19, loss_of_taste).

% Ask the user about symptoms
ask_user([]) :- 
    write('No more symptoms to check.'), nl, 
    !.

ask_user([Symptom | Rest]) :- 
    write('Do you have '), write(Symptom), write('? (yes/no): '), 
    read(Response),
    (   Response == yes -> 
        assertz(user_symptom(Symptom)), % Record the symptom if the answer is yes
        ask_user(Rest)  % Continue asking
    ;   ask_user(Rest) % Continue asking even if the answer is no
    ).

% Diagnose the disease based on the user's symptoms
diagnose(Disease) :-
    disease(Disease),
    findall(Symptom, symptom(Disease, Symptom), Symptoms),
    all_symptoms_present(Symptoms),  % Check if all symptoms of a disease are present
    write('You might have '), write(Disease), nl.

% Check if the symptoms of a disease match the user's symptoms
all_symptoms_present([]). % If no symptoms remain, it means all symptoms are present
all_symptoms_present([Symptom | Rest]) :-
    user_symptom(Symptom),  % If the user has the symptom
    all_symptoms_present(Rest). % Continue checking for remaining symptoms

% Main function to run the expert system
run :-
    write('Welcome to the Medical Diagnosis Expert System.'), nl,
    write('Please answer the following questions with "yes" or "no".'), nl,
    retractall(user_symptom(_)),  % Clear previous user responses
    diagnose(_),  % Attempt diagnosis
    !.

% Start the expert system
:- run.
