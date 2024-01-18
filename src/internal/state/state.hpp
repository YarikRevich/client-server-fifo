#pragma once

/**
 * Represents global state used for management purposes.
*/
class State {
private:
    /**
     * Represents result of the calculations.
    */
    static int sum;

public:
    /**
     * Retireves result of the calculations.
     * 
     * @return resulf ot the calculations.
    */
    static int getSum();

    /**
     * Sets result of the calculations.
     * 
     * @param value - result of the calculations.
    */
    static void setSum(int value); 
};