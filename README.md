# gpx

GPX was a physics library focused on real-time simulations.

It utilizes algorithms described in doc/GPX_CollisionHandling.pdf.

They provide accurate solutions.

The main idea was that each object delivers A and b coefficients, which lead to neat algorithm, 
that could simulate collisions (and friction*) beteween any type of object with the same piece of code.

I had no time to implement many features, like asynchronous updates (update rate depending on kinetic energy),
optimized version of algorithm for removal of negative impulses or dislocator classes to dislocate objects (to compensate small floating point arithmetics errors) in a better way.

I won't have time to play with it any more probably, so I'm putting code for archival purposes.

*Friction may have been removed for testing purposes. It was tested in older versions on sourceforge.

R.I.P.
