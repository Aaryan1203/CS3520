# Facility Reservation and Ticketing System

## Overview
This system is designed to manage facility reservations and ticketing for events organized by the City, organizations, and citizens. The system allows for reservation requests, ticket purchases, event cancellations, and maintains state persistence through file storage. It ensures a user-friendly experience with clear instructions and guidelines for users.

## Facility and Reservations
- **Operating Hours:** 8am to 11pm daily.
- **Guest Limit:** Maximum of 40 guests per event.
- **Reservation Priority:** City reservations get priority if made more than 1 week before the event. All other reservations are first-come-first-serve within 7 days of the event.
- **Reservation Costs:**
  - **Standard Service Charge:** $10 (non-refundable).
  - **Hourly Rates:**
    - Residents: $10/hour
    - Non-residents: $15/hour
    - Organizations: $20/hour
    - City: $5/hour
- **Cancellation Policy:**
  - No penalty if canceled 1 week before the event.
  - 1% penalty of rent if canceled within 7 days.
  - No refund if canceled within 24 hours of the event.
- **Reservation Limits:**
  - City: Up to 48 hours per week.
  - Organizations: Up to 36 hours per week.
  - Others: Up to 24 hours per week.
- **Event Types:** Public and Private.
  - **Public Events:** Tickets available for purchase.
  - **Private Events:** No ticket sales.
- **Room Layouts:** Meeting, Lecture, Wedding, and Dance Room styles.
  - City/Organization events limited to Meeting, Lecture, and Dance styles.
- **Budget for Facility:**
    - The facilities budget is all of the money it has made when users organize events. We store it in a field in the facility class

## Ticketing System
- **Event Viewing:** Users can view a list of events with details including event name, organizer, start and end time, ticket cost, room setup, and other requirements.
- **Ticket Purchase:** Users can purchase tickets for public events if available otherwise they will be put on a waitlist.
  - **Waitlist Management:** First-come-first-serve for available seats from cancellations.
  - **Refunds:** Automatic refunds if the event is canceled by the organizer.

## System Features
- **User Management:** Each user has a unique username (no passwords for users, but facility manager credentials are stored in `manager_credentials.txt`).
- **Menu Options:** Users can access features like view today’s schedule, request a reservation, make payment, view/edit user information, view reservations, cancel reservations, etc.
- **State Persistence:** Data is saved to files for persistence across sessions.
- **Dummy Data:** We have pre populated the data to allow for easy testing.

