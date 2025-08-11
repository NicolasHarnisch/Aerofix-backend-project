# Airline Ticket Reservation System / Version 1.1 🎟️

## 📜 Existing Features and Improvements

- **Seat Visualization**: Displays the layout of available and occupied seats. **(unchanged)**
- **User Interface**: The text-based interface has been enhanced to provide more information about seat availability, making the user experience more intuitive.
- **Class Selection**: Ability to choose between economy and business classes. **(unchanged)**
- **Reservation Storage**: Chosen seats are saved during the session. **(unchanged)**
- **Family Plans**: Support for family reservations of 3, 4, or 5 people, offering flexibility in choosing different rows for each seat.
- **Economy Seat Restrictions**: Prohibits booking of seats A and F in economy class, reserving them exclusively for business class. **(unchanged)**
- **Smarter Recommendation System for Economy Class**: The system now features enhanced logic that more efficiently locates available seats, ensuring optimized allocation for customers. This allows users to easily find seats that best meet their needs, making the booking experience faster and more practical.
- **Enhanced Recommendation System for Business Class**: The system now allows users to choose how they wish to be seated, with the following options:
  - **Sit separately, both near a window**: The system will recommend two seats near windows but separated from each other.
  - **Sit together, near a window**: The system will suggest two adjacent seats, with one of them being a window seat.
  - **Sit together, away from the window**: The system will recommend adjacent seats, both away from the window.
  - **Choose seats manually**: The user will have the option to manually select their desired seats, offering greater control over the reservation.

## 📜 New Features
- **Couples Plan**: Implementation of a dedicated feature for couples' reservations, allowing for a personalized and comfortable experience. Couples can:
  - Choose adjacent or separate seats according to their preferences.
  - Enjoy specific recommendations that ensure comfort and proximity, making the experience even more pleasant.
- **Modular Structure**: Highlights the organization of the code into modules or classes, which facilitates maintenance and the addition of new features in the future.
