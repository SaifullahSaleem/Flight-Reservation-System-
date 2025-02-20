
 	Airline Reservation System


1.	Introduction :

The Airline Reservation System is a comprehensive C++ program designed to address the complexities of managing airline operations. This system encapsulates a range of functionalities, including flight scheduling, reservation handling, and passenger information management. Employing an array of data structures, algorithms, and functions, the system aims to provide a robust framework for airlines to streamline their day-to-day operations.

2.	Code Overview:

 Data Structures :

2.1. FlightType Structure:
   - This structure serves as the backbone for representing individual flights, encapsulating crucial information such as flight number, departure and arrival cities, departure and arrival times, and the number of passengers onboard. Linked lists are employed to efficiently manage the next departure and arrival flights.

2.2. RouteType Structure:
   - Responsible for encapsulating data related to reservation routes, including the day of reservation, the number of hops, and the flight numbers associated with the route.

2.3. ReservationType Structure:
   - Manages passenger reservation details, including first and last names, trip types, and reservation routes. A linked list structure is utilized to facilitate the handling of multiple reservations.

2.4. CityType Structure:
   - Represents a city with a rich set of attributes such as its name, lists of departing and arriving flights, adjacent cities, distance, and the previous city (facilitating pathfinding).

2.5. FlightNumberListType Structure:
   - This structure efficiently maintains a list of flight numbers and their corresponding flight structures.

3.	Functions :

3.1. MakeFlightNode:
   - Dynamically creates and initializes a new flight node, providing a flexible mechanism for incorporating new flights into the system.

3.2. InitializeCityList:
   - Clears the city map, effectively initializing the city list to provide a clean slate for subsequent operations.

3.3. AddFlightToCityList:
   - Adds a flight to the departure and arrival lists of the respective cities. This function ensures that cities are appropriately updated with the new flight information.

3.4. AddFlightToFlightList:
   - Incorporates a new flight into the global flight list, maintaining a sorted order based on flight numbers.

3.5. MakeReserveNode:
   - Dynamically creates and initializes a new reservation node, catering to the diverse needs of passengers and their travel plans.

3.6. AddReservation:
   - Integrates a new reservation into the reservation list, ensuring proper ordering based on last names and first names.

3.7. DisplayFlightInfo:
   - Displays detailed information about a specific flight, facilitating a clear understanding of the flight's itinerary.

3.8. DisplayAllFlightsData:
   - Offers a comprehensive overview of all flights, enabling airline operators to review and manage their entire flight schedule.

3.9. DisplayAllCities:
   - Provides a concise list of all cities serviced by the airline, aiding in the evaluation of the airline's geographic coverage.

3.10. DisplayCitiesFromCity:
    - Outputs a list of cities reachable from a specific city, providing valuable insights into potential flight connections.

3.11. FindCityIndex:
    - Locates the index of a city within the city map, a crucial utility for various operations within the system.

3.12. DijkstraShortestPath:
    - Implements Dijkstra's algorithm to find the shortest path between two cities, facilitating efficient route planning and optimization.

3.13. DFSFindAllRoutes:
    - Utilizes Depth-First Search (DFS) to explore and discover all possible routes between two cities, offering a comprehensive perspective on available travel paths.

3.14. PrintPassengersOfFlight:
    - Prints a list of passengers for a specific flight, ordered by last name. This function aids in managing passenger information efficiently.

3.15. ShowDeparturesForCity:
    - Displays a list of flight departures from a city, sorted by departure time. This function contributes to providing real-time departure information.

3.16. ShowArrivalsForCity:
    - Presents a list of flight arrivals at a city, sorted by arrival time. This function assists in monitoring and managing incoming flights effectively.

3.17. main:
    - The main function orchestrates the entire system, initializing city lists, creating flights, managing reservations, and demonstrating the diverse functionalities of the Airline Reservation System.

4.	Code Execution:
The program unfolds by initializing the city list, creating flights, and seamlessly integrating them into the city and flight lists. Following this, reservations are handled, and the program showcases various functionalities, including displaying flight information, reservation details, passenger information, city coverage, and route planning.

5.	Conclusion:
The Airline Reservation System, as presented through this C++ program, represents a robust and extensible solution for managing the intricacies of airline operations. The amalgamation of well-structured data types, efficient algorithms, and user-friendly functions empowers airline operators to efficiently handle flight schedules, reservations, and passenger information. The versatility of the system allows for further expansion and customization to meet the specific needs and requirements of an evolving airline reservation landscape. The codebase serves as a foundation for the development of a sophisticated and comprehensive airline management system.
