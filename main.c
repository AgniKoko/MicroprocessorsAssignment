#include <MKL25Z4.H>

__asm void FuncATM(int userPIN, int *params, int *switches)
{
		MOVS R7, R2										// Save the switches to R7

		LDR R2, [R1, #4]              // Load notes100
    LDR R3, [R1, #8]              // Load notes50
    LDR R4, [R1, #12]             // Load notes20
    LDR R5, [R1, #16]             // Load notes10
    LDR R6, [R1, #20]             // Load notes5
    LDR R1, [R1]  								// Load notes200
	
		PUSH {R1, R2, R3, R4, R5, R6, LR}  

    // --- 1. Read PIN from memory (0200H) ---
    LDR R4, =0x1234             	// Load card PIN into R4
    LDR R5, =0x1ffff200           // Load address 0x0200 where card PIN will be stored
    STR R4, [R5]                  
		LDR R4, [R5]        

    // --- 2. Compare PIN ---
    CMP R0, R4                    // Compare userPIN (R0) with card PIN (R5)
    BNE PIN_ERROR                 // If the PINs do not match, go to error routine

		// --- 3. Handle banknotes if the PINs match ---
    // --- Handle 200€ banknotes ---
    POP {R1}                      // Restore notes200
    CMP R1, #0                    // Check if notes200 > 0
    BEQ SKIP_200
    LDR R0, [R7]                  // Load address of 200€ switch
LOOP_200
		MOVS R4, #1
		STR R4, [R0]                  // Write 1 (ON)
    SUBS R1, R1, #1               // Decrement notes200
		MOVS R4, #0
		STR R4, [R0]  								// Write 0 (OFF)
		CMP R1, #0                    // Check if notes200 > 0
    BNE LOOP_200                  
SKIP_200

    // --- Handle 100€ banknotes ---
    POP {R2}                      // Restore notes100
    CMP R2, #0
    BEQ SKIP_100
    LDR R0, [R7, #4]              // Load address of 100€ switch
LOOP_100
		MOVS R4, #1
		STR R4, [R0]                  // Write 1 (ON)
    SUBS R2, R2, #1               // Decrement notes100
		MOVS R4, #0
		STR R4, [R0]  								// Write 0 (OFF)
		CMP R2, #0                    
    BNE LOOP_100
SKIP_100

    // --- Handle 50€ banknotes ---
    POP {R3}                      // Restore notes50
    CMP R3, #0
    BEQ SKIP_50
    LDR R0, [R7, #8]              // Load address of 50€ switch
LOOP_50
		MOVS R4, #1
		STR R4, [R0]                  // Write 1 (ON)
    SUBS R3, R3, #1               // Decrement notes50
		MOVS R4, #0
		STR R4, [R0]  								// Write 0 (OFF)
		CMP R3, #0
    BNE LOOP_50
SKIP_50

    // --- Handle 20€ banknotes ---
    POP {R4}                      // Restore notes20
    CMP R4, #0
    BEQ SKIP_20
    LDR R0, [R7, #12]             // Load address of 20€ switch
LOOP_20
		MOVS R3, #1
		STR R3, [R0]                  // Write 1 (ON)
    SUBS R4, R4, #1               // Decrement notes20
		MOVS R3, #0
		STR R3, [R0]  								// Write 0 (OFF)
		CMP R4, #0
    BNE LOOP_20
SKIP_20

    // --- Handle 10€ banknotes ---
    POP {R5}                      // Restore notes10
    CMP R5, #0
    BEQ SKIP_10
    LDR R0, [R7, #16]             // Load address of 10€ switch
LOOP_10
		MOVS R4, #1
		STR R4, [R0]                  // Write 1 (ON)
    SUBS R5, R5, #1               // Decrement notes10
		MOVS R4, #0
		STR R4, [R0]  								// Write 0 (OFF)
		CMP R3, #0
    BNE LOOP_10
SKIP_10

    // --- Handle 5€ banknotes ---
    POP {R6}                      // Restore notes5
    CMP R6, #0
    BEQ SKIP_5
    LDR R0, [R7, #20]             // Load address of 5€ switch
LOOP_5
		MOVS R4, #1
		STR R4, [R0]                  // Write 1 (ON)
    SUBS R6, R6, #1               // Decrement notes5
		MOVS R4, #0
		STR R4, [R0]  								// Write 0 (OFF)
		CMP R3, #0
    BNE LOOP_5
SKIP_5

    B PIN_SUCC                     // Disable error indicator


PIN_ERROR
    // --- Activate error indicator (30H = 1) ---
    LDR R4, =0x1FFFF030           // Address for error indicator
    MOVS R0, #1                   
    STR R0, [R4]                  // Store the error indicator
		
		B EXIT
		
PIN_SUCC
    // --- Disable error indicator (30H = 0) ---
    LDR R4, =0x1FFFF030           // Address for error indicator
    MOVS R0, #0                   
    STR R0, [R4]                  // Store the error indicator
		
		B EXIT

EXIT
    POP {R1, R2, R3, R4}         // Restore R1-R4
    POP {R5, R6}                 // Restore R5-R6
    POP {R7}                     // Restore LR temporarily in R7
    MOV LR, R7                   // Move R7 to LR

    BX LR                        // Return from function           
}



int main(void)
{
    int userPIN = 0x5555; 
	
		int switches[6];        			// Array for the switches
		
    // Banknote counts
    int notes200 = 5;             // 5 x 200€
    int notes100 = 2;             // 2 x 100€
    int notes50 = 3;              // 3 x 50€
    int notes20 = 4;              // 4 x 20€
    int notes10 = 0;              // 0 x 10€
    int notes5 = 1;               // 1 x 5€
   
		int params[6];                // Declare the params array
		params[2] = notes50;          // notes50

		// Initialize the params array with the banknote counts
		params[0] = notes200;         // notes200
		params[1] = notes100;         // notes100
		params[3] = notes20;          // notes20
		params[4] = notes10;          // notes10
		params[5] = notes5;           // notes5

		switches[0] = 0x1FFFF010; 		// notes200
		switches[1] = 0x1FFFF014; 		// notes100
		switches[2] = 0x1FFFF018; 		// notes50
		switches[3] = 0x1FFFF01C; 		// notes20
		switches[4] = 0x1FFFF020; 		// notes10
		switches[5] = 0x1FFFF024; 		// notes5

    FuncATM(userPIN, params, switches);

    while (1);
}
