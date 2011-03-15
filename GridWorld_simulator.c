#include <time.h>
#include <unistd.h>
#include <gsl/gsl_matrix.h>
#include "GridWorld.h"
#include "greedy.h"
#include "utils.h"
#define TRANS_WIDTH 7 /*2*2 for s and s', 1 each for a,r,eoe*/
#define MAX_EPISODE_LENGTH (2*GRID_HEIGHT+2*GRID_WIDTH)

unsigned int g_iNb_samples = 0;

/* Simulate nbEpisodes episodes in the Gridworld using greedy_policy()*/
gsl_matrix* gridworld_simulator( int nbEpisodes ){
  srand(time(NULL)+getpid()); rand(); rand();rand();
  gsl_matrix* transitions = gsl_matrix_alloc( nbEpisodes*MAX_EPISODE_LENGTH, TRANS_WIDTH );
  unsigned int state_x = 1;
  unsigned int state_y = 1;
  gsl_matrix* state = gsl_matrix_alloc( 1, 2 );
  unsigned int j = 0; //Index in transitions
  for( unsigned int i = 0 ; i < nbEpisodes ; i++ ){
    unsigned int nb_steps = 0;
    int eoe = 1;
    while( eoe==1 ){
      nb_steps++;
      g_iNb_samples++;
      if( nb_steps == MAX_EPISODE_LENGTH ){
	eoe = 0;
      }
      gsl_matrix_set( state, 0, 0, (double)state_x );
      gsl_matrix_set( state, 0, 1, (double)state_y );
      unsigned int next_state_x = state_x;
      unsigned int next_state_y = state_y;
      gsl_matrix* mAction = greedy_policy( state );
      unsigned int action = 
	(unsigned int)gsl_matrix_get( mAction, 0, 0 );
      gsl_matrix_free( mAction );
      unsigned int true_action = action;
      int is_noisy = rand_1_in_10();
      if( is_noisy ){
	true_action = random_int( 1, 4 );
      }
      switch( true_action ){
      case UP:
	next_state_y++;
	if( next_state_y > GRID_HEIGHT ){
	  next_state_y = GRID_HEIGHT;
	}
	break;
      case DOWN:
	next_state_y--;
	if( next_state_y < 1 ){
	  next_state_y = 1;
	}
	break;
      case RIGHT:
	next_state_x++;
	if( next_state_x > GRID_WIDTH ){
	  next_state_x = GRID_WIDTH;
	}
	break;
      case LEFT:
	next_state_x--;
	if( next_state_x < 1 ){
	  next_state_x = 1;
	}
	break;
      }
      int reward = 0;
      if( state_x == GRID_WIDTH && 
	  state_y == GRID_HEIGHT ){
	reward = 1;
	eoe = 0;
      }
      gsl_matrix_set( transitions, j, 0, (double)state_x );
      gsl_matrix_set( transitions, j, 1, (double)state_y );
      gsl_matrix_set( transitions, j, 2, (double)action );
      gsl_matrix_set( transitions, j, 3, (double)next_state_x );
      gsl_matrix_set( transitions, j, 4, (double)next_state_y );
      gsl_matrix_set( transitions, j, 5, (double)reward );
      gsl_matrix_set( transitions, j, 6, (double)eoe );
      j++;
      if( eoe == 1 ){
	state_x = next_state_x;
	state_y = next_state_y;
      }else{
	state_x = 1;
	state_y = 1;
      }
    }
  }
  gsl_matrix* answer = gsl_matrix_alloc( j, TRANS_WIDTH );
  gsl_matrix_view trans_v = 
    gsl_matrix_submatrix( transitions, 0, 0, j, TRANS_WIDTH );
  gsl_matrix_memcpy( answer, &trans_v.matrix );
  gsl_matrix_free( transitions );
  return answer;
}
