/*
 * Queue.java
 *
 * Created on March 6, 2008, 1:17 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package que;

import javaapplication21.*;

public interface Queue
{
    /**
     * Insert a new item into the queue.
     * @param x the item to insert.
     */
    void  enqueue( int x );
    
    /**
     * Get the least recently inserted item in the queue.
     * Does not alter the queue.
     * @return the least recently inserted item in the queue.
     * @exception UnderflowException if the queue is empty.
     */
    int getFront( );

    /**
     * Return and remove the least recently inserted item
     * from the queue.
     * @return the least recently inserted item in the queue.
     * @exception UnderflowException if the queue is empty.
     */
    int dequeue( );

    /**
     * Test if the queue is logically empty.
     * @return true if empty, false otherwise.
     */
    boolean isEmpty( );

    /**
     * Make the queue logically empty.
     */
    void makeEmpty( );
}