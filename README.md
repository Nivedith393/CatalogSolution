# CatalogSolution
#Polynomial Secret Solver#

This project implements a simplified version of Shamir's Secret Sharing algorithm to solve for the constant term c of a polynomial using given roots from a JSON file. The solution involves decoding values from different bases and applying Lagrange Interpolation to retrieve the secret.

Features
JSON Parsing: Parses input data from a JSON file to retrieve polynomial roots.

Base Decoding: Decodes y values from different bases (binary, decimal, hex, etc.).

Lagrange Interpolation: Uses Lagrange interpolation to calculate the constant term c of the polynomial.

Technologies Used

C Programming Language

cJSON library for JSON parsing

Lagrange Interpolation for polynomial solving
