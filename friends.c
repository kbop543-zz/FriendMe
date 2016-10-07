#include "friends.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>




/*
 * Create a new user with the given name.  Insert it at the tail of the list
 * of users whose head is pointed to by *user_ptr_add.
 *
 * Return:
 *   - 0 if successful
 *   - 1 if a user by this name already exists in this list
 *   - 2 if the given name cannot fit in the 'name' array
 *       (don't forget about the null terminator)
 */
int create_user(const char *name, User **user_ptr_add) {

	User *new_user = malloc(sizeof(User));

	strcpy(new_user->name,name); //set name
	new_user->next = NULL; //set next
	new_user->profile_pic[0] = '\0'; //set profile pic
	new_user->first_post = NULL; //set post to null

	for (int i=0;i<MAX_FRIENDS;i++){ //set friends array to null
		new_user->friends[i] = NULL;
	}

	User *curr = *user_ptr_add;


	if (new_user == NULL){ //checking if malloc failed
		exit(-1);
	}

	if (*user_ptr_add == NULL){ //if the list is empty
		if ((strlen(name) +1) <= MAX_NAME){ //checks if within buffer
			*user_ptr_add = new_user;
			return 0;
		}else{
			return 2;
		}

	} while(curr->next != NULL){ //if list is not empty
		if ((strlen(name) +1) > MAX_NAME){ //checks if within buffer
			return 2;
		}
		if (strcmp(curr->name,name) ==0){ //checks if name already exists in list
			return 1;
		}
		curr = curr->next;
	}
	curr->next = new_user;
	return 0;
		
}


		
	
/*
 * Return a pointer to the user with this name in
 * the list starting with head. Return NULL if no such user exists.
 *
 * NOTE: You'll likely need to cast a (const User *) to a (User *)
 * to satisfy the prototype without warnings.
 */
User *find_user(const char *name, const User *head) {

	    
	        User *curr = (struct user *) head;
		while (curr != NULL){ //checks if name already exists in list
			if (strcmp(curr->name,name) ==0){
				return curr;
		}
	        curr = curr->next;
	}
		return NULL;
}


/*
 * Print the usernames of all users in the list starting at curr.
 * Names should be printed to standard output, one per line.
 */
void list_users(const User *curr) {



	User *front =  (User *)curr;
	printf("User List\n");
	while (front != NULL){
		printf("%s\n",front->name);
		front = front->next;
	}
}

/*
 * Change the filename for the profile pic of the given user.
 *
 * Return:
 *   - 0 on success.
 *   - 1 if the file does not exist.
 *   - 2 if the filename is too long.
 */
int update_pic(User *user, const char *filename) {

	FILE *user_pic;

	user_pic = fopen(filename,"r");
	if(user_pic == NULL){ //if file doesnt exist
		return 1;
	}

	if((strlen(filename) +1) > MAX_NAME){ //checks if within buffer
		return 2;
	}
	strcpy(user->profile_pic,filename);
	fclose(user_pic);
	
	return 0;
}


/*
 * Make two users friends with each other.  This is symmetric - a pointer to
 * each user must be stored in the 'friends' array of the other.
 *
 * New friends must be added in the first empty spot in the 'friends' array.
 *
 * Return:
 *   - 0 on success.
 *   - 1 if the two users are already friends.
 *   - 2 if the users are not already friends, but at least one already has
 *     MAX_FRIENDS friends.
 *   - 3 if the same user is passed in twice.
 *   - 4 if at least one user does not exist.
 *
 * Do not modify either user if the result is a failure.
 * NOTE: If multiple errors apply, return the *largest* error code that applies.
 */
int make_friends(const char *name1, const char *name2, User *head) {

	int i = 0;
	int j = 0;

	 if(find_user(name2,head) ==NULL || find_user(name1,head) ==NULL){ //if user doesn't exist
		return 4;
	 }


	 else if(strcmp(name1,name2) ==0){
		return 3;


	}	
	else if(find_user(name1,head) || find_user(name2,head)){ //if either user exists
		User *namee1 = (find_user(name1,head)); 
		User *namee2 = (find_user(name2,head));
		if (namee1->friends[MAX_FRIENDS -1] != NULL
			    || namee2->friends[MAX_FRIENDS-1] != NULL){ //if either user has MAX_FRIENDS friends
		    return 2;
		    }

		    while (namee1->friends[i] != NULL && i<MAX_FRIENDS){
		    if(namee1->friends[i] == namee2){ //if user are already friends
		    return 1;
		    }
		    i++;
		    
		    }
		    namee1->friends[i] = namee2;
		    

		    while (namee2->friends[j] != NULL && j<MAX_FRIENDS){
		    if(namee2->friends[j] == namee1){ //if user are already friends
		    return 1;
		    }
		    j++;
		    }
		    namee2->friends[j] = namee1;
		    return 0;
	}
	return 4;
}

		    
/*
 * Print a user profile.
 * For an example of the required output format, see the example output
 * linked from the handout.
 * Return:
 *   - 0 on success.
 *   - 1 if the user is NULL.
 */
int print_user(const User *user) {

	int i = 0;
	FILE *user_pic;
	char line[500];

	if(find_user(user->name,user) == NULL){ //if user is NULL
		return 1;
	}


	Post *post = user->first_post;


		
	if (user->profile_pic[0] == '\0'){ //if profile pic isnt set
		printf("Name: %s\n\n------------------------------------------\nFriends:\n",user->name);
		if(user->friends[0] != NULL){ //checks if there are friends added
			while( (i<MAX_FRIENDS) && (user->friends[i] != NULL)){
		        printf("%s\n",user->friends[i]->name);
		        i++;
		}
			printf("------------------------------------------\n");

			
		}else{
			printf("------------------------------------------\n");
		
		}
		if(post!= NULL){ //checks if posts have been added
			printf("Posts:\nFrom:%s\nDate:%s\n\n%s\n",post->author,ctime(post->date),post->contents);
			if(post->next != NULL){
				post = post->next;
				while(post !=NULL){
					printf("\n===\n\nFrom:%s\nDate:%s\n\n%s\n",post->author
					,ctime(post->date),post->contents);
					post= post->next;
				}
				printf("------------------------------------------\n");
				return 0;
			}
			printf("------------------------------------------\n");
			return 0;



			
			
		}else if(post ==NULL){
		printf("Posts:\n------------------------------------------\n");
		return 0;
	}
	}//else, profile pic is set
	user_pic = fopen(user->profile_pic,"r");

	while(fgets(line, 499, user_pic)!= NULL){
		printf("%s",line);
	}
	printf("\n\nName: %s\n\n------------------------------------------\nFriends:\n",user->name);
	if(user->friends[0] != NULL){ //checks if there are friends added
			while((i<MAX_FRIENDS) && (user->friends[i] != NULL)){
		        printf("%s\n",user->friends[i]->name);
		        i++;
		}
			printf("------------------------------------------\n");


			
		}else{
			printf("------------------------------------------\n");
		
		}
		if(post!= NULL){ //checks if posts have been added
			printf("Posts:\nFrom:%s\nDate:%s\n\n%s\n",post->author,ctime(post->date),post->contents);
			if(post->next != NULL){
				post = post->next;
				while(post !=NULL){
					printf("\n===\n\nFrom:%s\nDate:%s\n\n%s\n",post->author
					,ctime(post->date),post->contents);
					post= post->next;
				}
				printf("------------------------------------------\n");
				return 0;
			}
			printf("------------------------------------------\n");
			return 0;



			
			
		}else if(post ==NULL){
		printf("Posts:\n------------------------------------------\n");
		return 0;
	}
return 0;
}
	

		
    	


/*
 * Make a new post from 'author' to the 'target' user,
 * containing the given contents, IF the users are friends.
 *
 * Insert the new post at the *front* of the user's list of posts.
 *
 * Use the 'time' function to store the current time.
 *
 * 'contents' is a pointer to heap-allocated memory - you do not need
 * to allocate more memory to store the contents of the post.
 *
 * Return:
 *   - 0 on success
 *   - 1 if users exist but are not friends
 *   - 2 if either User pointer is NULL
 */
int make_post(const User *author, User *target, char *contents) {

	int i = 0;

	User *authorr = find_user(author->name,author);
	User *targett = find_user(target->name,target);


	if(authorr == NULL || targett == NULL){ //if User pointers are null
		return 2;
	}

	
	Post *new_post = malloc(sizeof(Post));
	new_post->contents = contents; //set contents
	strcpy(new_post->author,author->name); //set author

	time_t *post_time = malloc(sizeof(time_t)); //set date

	*post_time = time(0);
	new_post->date = post_time;

        	
	if (new_post == NULL){ //checking if malloc failed
		exit(-1);
	}

	if (post_time == NULL){ //checking if malloc failed
		exit(-1);
	}



			while (targett->friends[i] != NULL){
		    if(targett->friends[i] == authorr){ //if user are already friends
			    if (targett->first_post == NULL){ //if no posts have been added yet
				   targett->first_post = new_post;
				   new_post->next = NULL;
				   return 0;
				   

			    }
			    new_post->next = targett->first_post;
			    targett->first_post = new_post;
			    return 0;

		    }
		    i++;
		}
	return 1; //if they aren't friends

}


/*
 * From the list pointed to by *user_ptr_del, delete the user
 * with the given name.
 * Remove the deleted user from any lists of friends.
 *
 * Return:
 *   - 0 on success.
 *   - 1 if a user with this name does not exist.
 */

int delete_user(const char *name, User **user_ptr_del) {

	int i = 0;
	

    if (find_user(name,*user_ptr_del) == NULL){
	    return 1;
    }
    User *curr = *user_ptr_del;
    while (curr != NULL){
	    User *next = curr->next; 
	    if (strcmp(curr->name,name)== 0){ //if its the head to be deleted
		    while(curr->friends[i] != NULL){ 
			    User *friend = curr->friends[i];
			    
			    //traverses through friends of user to be deleted
			    int j = 0;
			    while(friend->friends[j] != NULL){ 
				//goes into friend[i]'s friends list				   
				    if(strcmp(friend->friends[j]->name,name) == 0){ 
      //finds the place where the user to be deleted is in friend's friends list
						    if(friend->friends[j+1] == NULL){ 
			//if the user to be deleted is at the end of array thats not NULL
							    friend->friends[j] = NULL;
						    }
						    int k = j;
						    while(friend->friends[k] != NULL){
					 //deletes user in friend array by filling that spot with the values in indexes after it
							    friend->friends[k] = friend->friends[k+1];
							    k++;
						    }
				    }
				    j++;
			    }
			    i++;
		    }
		    *user_ptr_del = curr->next;	    
		    curr->next = NULL;
		    Post *post = curr->first_post;
		    while(post != NULL){ //free every post the user wrote
			    Post *next_post = post->next;
			    free(post);  
			    post = next_post;
		    }
		    free(curr); //free the user
		    return 0;
		    
	    } else if (strcmp(next->name,name) ==0){ //anything other than the head to be deleted
		    while(next->friends[i] != NULL){ 
			    User *friend = next->friends[i];
			    
			    //traverses through friends of user to be deleted
			    int j = 0;
			    while(friend->friends[j] != NULL){ 
				//goes into friend[i]'s friends list				   
				    if(strcmp(friend->friends[j]->name,name) == 0){ 
      //finds the place where the user to be deleted is in friend's friends list
						    if(friend->friends[j+1] == NULL){ 
			//if the user to be deleted is at the end of array thats not NULL
							    friend->friends[j] = NULL;
							    
						    }
						    
						    int k = j;
						    while(friend->friends[k] != NULL){
							    friend->friends[k] = friend->friends[k+1];
							    k++;
						    }
						    
				    }
				    j++;
			    }
			    i++;
		    }
		    	    
		    curr->next = next->next;
		    Post *post = next->first_post;
		    while(post != NULL){ //free every post the user wrote
			    Post *next_post = post->next;
			    free(post); 
			    post = next_post;
		    }
		    free(next); // free the user
		    return 0;
		    
	    }
	    curr = curr->next;
	    
    }
    return 0;
    
}



