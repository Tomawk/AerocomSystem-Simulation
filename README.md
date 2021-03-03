# aerocom_system_group5

Omnet++ Simulation group project done for the exam of Performance Evaluation at my second cycle degree in Computer Engineering.

# Project text

An aero system is composed of N Aircrafts (ACs). Each AC communicates with a control tower
(CT) generating one packet of fixed size every k seconds, where the latter is a random variable to be
described later.

ACs have five data-links (DL) available for communication with the CT, and can use only one of
them at a time as serving DL. The first serving Each DL has a time-varying capacity: every t
seconds a new target capacity is selected and the capacity will linearly change from the current one
to the target one, which is reached after t seconds. t is a random variable to be described later.
Before performing each transmission, the AC can select a new serving DL the following way: if the
capacity between transmission i-2 and i-1 decreased by more than X%, the AC will perform a DL
selection, which takes S seconds. The new DL is selected as the one with the highest capacity at the
current time.

Measure at least the response time for various values of X and S, and compare the results.
At least the following two scenarios have to be evaluated:
* Exponential distribution of t and k;
* Lognormal distribution of t and k;
In all cases, it is up to the team to calibrate the scenarios so that meaningful results are obtained.
