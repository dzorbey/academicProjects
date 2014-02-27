#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_TICKETS 100
#define NUM_AGENTS 5
#define NUM_LINES 10

int total_sold = 0;
pthread_mutex_t tickets_sold_lock = PTHREAD_MUTEX_INITIALIZER;

queue line_of_callers;

/* A lock for the queue of callers. */
pthread_mutex_t line_lock = PTHREAD_MUTEX_INITIALIZER;

/* Semaphore representing the current number of callers in line. */
sem_t num_in_line;

/*Semaphores for communication from agents to phone lines to indicate
   when a call is finished. Basically used for the agent to tell
   the line to "hang up" the call. */
sem_t lines[NUM_LINES];

/* Mutex and condition variable for the bookkeeper to use to 
   wait for all the tickets to be sold. */
pthread_mutex_t finish_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t finish_cond = PTHREAD_COND_INITIALIZER;

void* call_line (void* data)
{
   /* An identifier for which line this is */
   int my_num = *((int*)data);
   while (1)
   {
      /* Dummy function that simulates waiting for this line
     to ring. */
     wait_for_caller ();
     /* Get the lock for the line to make sure two call lines
       don't add a caller to the line at the same time. */
     pthread_mutex_lock (&line_lock);
     queue_add (line_of_callers, my_num);
     pthread_mutex_unlock (&line_lock);

     /* Signal the semaphore for the total number of callers in
        line so that one of the agents will pick up. */
     sem_post (&num_in_line);

      /* Wait on the signal from the ticket agent so that we know
         that the call has been handled and can therefore
         handle another call on this line. */
     sem_wait (&lines[my_num]);
   }

   return NULL;
}

void* ticket_agent (void* foo)
{
   int currently_helping;
   while (1)
   {
      /* Wait until there is a caller in the line. */
      sem_wait (&num_in_line);

      /* Get the lock for the line and take the first caller 
         in line off of the list.*/
      pthread_mutex_lock (&line_lock);
      currently_helping = queue_remove (line_of_callers);
      pthread_mutex_unlock (&line_lock);
         printf("Helping caller on line %d.\n", currently_helping);
         pthread_mutex_lock (&tickets_sold_lock);

      if (total_sold < NUM_TICKETS)
      {
         /* If we still have tickets left, sell the ticket
            to the customer. */
         if (sell_ticket_to_customer ())
         {
            /* Add one to the total number sold. If we are
               all sold out now, tell the bookkeeper to clean
               up through the condition variable. */
            pthread_mutex_lock (&finish_mutex);
            total_sold++;
            if (total_sold == NUM_TICKETS)
            pthread_cond_broadcast (&finish_cond);
            pthread_mutex_unlock (&finish_mutex);
         }
      }
      else
      {
         /* Otherwise, tell them we are sold out. */
         tell_customer_sold_out ();
      }
      pthread_mutex_unlock (&tickets_sold_lock);

      /* Signal the semaphore telling the line that this 
         call is over. */
      sem_post (&lines[currently_helping]);
         printf ("Done with caller on line %d.\n", currently_helping);
   }

   return NULL;
}

void* bookkeeper (void* foo)
{
   /* Use the condition wait to make sure that we do not do any
      bookkeeping until the total_sold is equal to the total
      number of tickets. */
   pthread_mutex_lock (&finish_mutex);
   while (total_sold < NUM_TICKETS)
      pthread_cond_wait (&finish_cond, &finish_mutex);

   do_bookkeeping ();

   pthread_mutex_unlock (&finish_mutex);

   return NULL;
}

int main ()
{
   pthread_t agents[NUM_AGENTS];
   pthread_t phone_lines[NUM_LINES];
   pthread_t cleanup;
   void* return_val;
   int i;

   srand (time (0));

   /* Initialize the semaphores. */
   sem_init (&num_in_line, 0, 0);
   for (i = 0; i < NUM_LINES; i++)
   sem_init (&(lines[i]), 0, 0);

   /* Create the ticket agents. */
   for (i = 0; i < NUM_AGENTS; i++)
   pthread_create (&agents[i], NULL, ticket_agent, NULL);

   /* Create the lines for callers. */
   for (i = 0; i < NUM_LINES; i++)
   pthread_create (&phone_lines[i], NULL, call_line, &i);

   /* Create the bookkeeper. */
   pthread_create (&cleanup, NULL, bookkeeper, NULL);
   /* We only need to wait on the bookkeeper because we know 
      that once the bookkeeper is done, we are done with 
      the program and can exit. The other threads will loop
      forever handling calls. */
   pthread_join (cleanup, &return_val);

      printf ("Sold all the tickets: %d\n", total_sold);
}