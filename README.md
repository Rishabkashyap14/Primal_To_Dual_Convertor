# Primal_To_Dual_Convertor

Conversion from the Primal form of a problem to its dual can be a tricky process and this repository looks into a logically efficient approach for easy conversion process by minimizing the ambiguity. 

## How does it work?

The process behind it is simple: Provide the inputs as written in the __main()__ function of the file. This initializes the primal problem. The conversion process will take place provided it is a valid primal, else the program exits.  

Once the primal problem has been entered, the first step is the conversion into its canonical form having all signs either <= or >=. This is then converted into its dual canonical form with all signs either <= or >= again. Finally, to convert it into the general form, the signs are broken down on comparison with the domain of each variable displayed as the parameters. 

## How can I execute this? 

Clone the repository on your local system, and simply run:  
`make`  
`./conversion`  

To clean any files newly created, simply use:  
`make clean`
