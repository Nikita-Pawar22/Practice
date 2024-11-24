% Facts: These describe family relationships with Indian names.

% Parent-Child relationships
parent(amit, raj).         % Amit is the parent of Raj
parent(amit, simran).      % Amit is the parent of Simran
parent(raj, aarya).        % Raj is the parent of Aarya
parent(simran, arjun).     % Simran is the parent of Arjun
parent(simran, meera).     % Simran is the parent of Meera
parent(aarya, yash).       % Aarya is the parent of Yash
parent(meera, diya).       % Meera is the parent of Diya
parent(arjun, rohan).      % Arjun is the parent of Rohan

% Rules: These define relationships based on facts.

% Siblings are people who share at least one parent.
siblings(X, Y) :- parent(P, X), parent(P, Y), X \= Y.

% Grandparents are the parents of the parents.
grandparent(X, Y) :- parent(X, P), parent(P, Y).

% A person is an ancestor if they are a parent or a grandparent (recursively).
ancestor(X, Y) :- parent(X, Y).                   % Base case
ancestor(X, Y) :- parent(X, P), ancestor(P, Y).  % Recursive case

% Query Example:
% 1. Who are Raj's parents?
% ?- parent(X, raj).

% 2. Who are the siblings of Simran?
% ?- siblings(simran, Sibling).

% 3. Who are Aarya's grandparents?
% ?- grandparent(X, aarya).

% 4. Who are the ancestors of Diya?
% ?- ancestor(X, diya).
