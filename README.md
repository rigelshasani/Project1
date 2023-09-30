# OOP
OOP345 Project

This project will be dealing with workstations in an assembly line. Each of the stations holds a series of stock items, which are specific to the station. A line manager will be moving customer orders along the line filling the orders at each station as requested.

Each customer order consists of a list of items that need to be filled. Each station processes a queue of orders by filling the next order in the queue if that order requests the station's item and that item is in stock. The line manager keeps moving the customer orders from the station until all orders have been processed. Any station that has used all the items in the stock cannot fill any more orders.

At the end of the line, orders are either completed or incomplete due to a lack of inventory at one or more stations. The simulator lists the completed orders and those that are incomplete once the line manager has finished processing all orders.

This project is divided into 3 milestones.