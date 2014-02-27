/*
 * ArrayQueue.java
 *
 * Created on March 6, 2008, 1:15 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package que;

import javaapplication21.*;

public class ArrayQueue implements Queue
{
    /**
     * Construct the queue.
     */
    public ArrayQueue( )
    {
        theArray = new int[ DEFAULT_CAPACITY ];
        
        makeEmpty( );
    }

    /**
     * Test if the queue is logically empty.
     * @return true if empty, false otherwise.
     */
    public boolean isEmpty( )
    {
        //if(currentSize==0) {
        //    return true;
       // }
        return currentSize == 0;
    }

    /**
     * Make the queue logically empty.
     */
    public void makeEmpty( )
    {
        currentSize = 0;
        front = 0;
        back = -1;
        
    }

    /**
     * Return and remove the least recently inserted item
     * from the queue.
     * @return the least recently inserted item in the queue.
     * @throws UnderflowException if the queue is empty.
     */
    public int dequeue( )
    {
        
        //if( isEmpty( ) )
           // throw new UnderflowException( "ArrayQueue dequeue" );
        currentSize--;
        
        int returnvalue = theArray[ front ];
        front = increment( front );
        return returnvalue;
    }
    
    /**
     * Get the least recently inserted item in the queue.
     * Does not alter the queue.
     * @return the least recently inserted item in the queue.
     * @throws UnderflowException if the queue is empty.
     */
    public int getFront( )
    {
        //if( isEmpty( ) )
           // throw new UnderflowException( "ArrayQueue getFront" );
        return theArray[ front ];
    }

    /**
     * Insert a new item into the queue.
     * @param x the item to insert.
     */
    public void enqueue( int x )
    {
       
        if( currentSize == theArray.length )
            doubleQueue( );
        back = increment( back );
        theArray[ back ] = x;
        currentSize++;   
    }

    /**
     * Internal method to increment with wraparound.
     * @param x any index in theArray's range.
     * @return x+1, or 0 if x is at the end of theArray.
     */
    private int increment( int x )
    {
        if( ++x == theArray.length )
            x = 0;
        return x;
    }
    
    /**
     * Internal method to expand theArray.
     */
    private void doubleQueue( )
    {
        int[ ] newArray;

        newArray = new int[ theArray.length * 2 ];

            // Copy elements that are logically in the queue
        for( int i = 0; i < currentSize; i++, front = increment( front ) )
            newArray[ i ] = theArray[ front ];

        theArray = newArray;
        front = 0;
        back = currentSize - 1;
    }

    private int[ ] theArray;
    public int        currentSize;
    public int        front;
    public int        back;
    private static final int DEFAULT_CAPACITY = 10000;
    
    
}