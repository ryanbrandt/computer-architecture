#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/* globals */
int miss;
int hit;
int mr;
struct Line** cache;
unsigned long int count;
int mw;

typedef struct Line{
	unsigned long int tag;
	int valid;
	unsigned long int time;
}Line;


Line** getCache(int setnum,int assoc)
{
 	int i,j;
  	cache=(Line**)malloc(setnum*sizeof(Line*));
  	for(i=0;i<setnum;i++)
	{
    		cache[i]=(Line*)malloc((assoc)*sizeof(Line));
  	}
  	for(i=0;i<setnum;i++)
	{
    		for(j=0;j<assoc;j++)
		{
         		cache[i][j].valid=0;
    		}
  	}
	return cache;
}


void resetCache(int setnum, int assoc)
{
	int i,j;
	for(i=0;i<setnum;i++)
	{
		for(j=0;j<assoc;j++)
		{
			cache[i][j].tag=0;
			cache[i][j].valid=0;
			cache[i][j].time=0;
		}
	}
	miss=0;
	hit=0;
	mr=0;
	mw=0;
	count=0;
}
void prefetchww(unsigned long int tagindex,unsigned long int setindex,int assoc)
{
	int i,j,min;
	for(i=0;i<assoc;i++)
	{
		if(cache[setindex][i].valid==0){
			mr++;
			count++;
			cache[setindex][i].valid=1;
			cache[setindex][i].tag=tagindex;
			cache[setindex][i].time=count;
			return;
		}
		else
		{
			if(cache[setindex][i].tag==tagindex)
			{
				return;	
			}	
			if(i==(assoc-1))
			{
				mr++;
				min=0;
				for(j=0;j<assoc;j++)
				{
					if(cache[setindex][j].time<=cache[setindex][min].time)
					{
						min=j;
					}	
				}
			cache[setindex][min].valid=1;
	        	cache[setindex][min].tag=tagindex;
	        	count++;
	        	cache[setindex][min].time=count;
			return;
	   		}
		}
	}
}
void prefetchrr(unsigned long int tagindex,unsigned long int setindex,int assoc)
{
	int i,j,min;
	for(i=0;i<assoc;i++)
	{
		if(cache[setindex][i].valid==0)
		{
			mr++;
			count++;
			cache[setindex][i].valid=1;
			cache[setindex][i].tag=tagindex;
			cache[setindex][i].time=count;
			return;
		}
		else
		{
			if(cache[setindex][i].tag==tagindex)
			{
			return;
			}	
			if(i==(assoc-1))
			{
				mr++;
				min=0;
				for(j=0;j<assoc;j++)
				{
					if(cache[setindex][j].time<=cache[setindex][min].time)
					{
						min=j;
					}	
				}
			cache[setindex][min].valid=1;
	        	cache[setindex][min].tag=tagindex;
	        	count++;
	        	cache[setindex][min].time=count;
			return;
			}
		}
	}
}
/* do read operation, check set index, miss if DNE in set, then write, else update time */
void doRead(unsigned long int tagindex,unsigned long int setindex,int assoc)
{
	int i,j,min;
	for(i=0;i<assoc;i++)
	{
		if(cache[setindex][i].valid==0)
		{
			miss++;
			mr++;
			count++;
			cache[setindex][i].valid=1; 
			cache[setindex][i].tag=tagindex;
			cache[setindex][i].time=count;
			return;
		}
		else
		{
			if(cache[setindex][i].tag==tagindex)
			{
				hit++;
				count++;
				cache[setindex][i].time=count;
				return;
			}
			
			if(i==(assoc-1))
			{
				miss++;
				mr++;
				min=0;
				for(j=0;j<assoc;j++)
				{
					if(cache[setindex][j].time<=cache[setindex][min].time)
					{
						min=j;
					}	
				}
			cache[setindex][min].valid=1;
	        	cache[setindex][min].tag=tagindex;
	        	count++;
	        	cache[setindex][min].time=count;
			return;
			}
		}
	}
}
/* do write operation, check set index, insert if DNE in set */
void doWrite(unsigned long int tagindex,unsigned long int setindex,int assoc)
{
	int i,j,min;
	for(i=0;i<assoc;i++)
	{
		if(cache[setindex][i].valid==0)
		{
			miss++;
			mr++;
			mw++;
			count++;
			cache[setindex][i].valid=1;
			cache[setindex][i].tag=tagindex;
			cache[setindex][i].time=count;
			return;
		}
		else
		{
			if(cache[setindex][i].tag==tagindex)
			{
				hit++;
				mw++;
				count++;
				cache[setindex][i].time=count;
				return;
			}	
			if(i==(assoc-1))
			{
				miss++;
				mr++;
				mw++;
				min=0;
				for(j=0;j<assoc;j++)
				{
					if(cache[setindex][j].time<=cache[setindex][min].time)
					{
						min=j;
					}	
				}
			cache[setindex][min].valid=1;
	        	cache[setindex][min].tag=tagindex;
	        	count++;
	        	cache[setindex][min].time=count;
			return;
			}
		}
	}
}
void prefetchwwl(unsigned long int tagindex,unsigned long int setindex,int assoc)
{
	int i,j,min;
	for(i=0;i<assoc;i++)
	{
		if(cache[setindex][i].valid==0)
		{
			mr++;
			count++;
			cache[setindex][i].valid=1;
			cache[setindex][i].tag=tagindex;
			cache[setindex][i].time=count;	
			return;
		}
		else
		{
			if(cache[setindex][i].tag==tagindex)
			{
				return;
			}
			if(i==(assoc-1))
			{
				mr++;
				min=0;
				for(j=0;j<assoc;j++)
				{
					if(cache[setindex][j].time<=cache[setindex][min].time)
					{
						min=j;
					}	
				}
			cache[setindex][min].valid=1;
	        	cache[setindex][min].tag=tagindex;
	        	count++;
	        	cache[setindex][min].time=count;
	        	return;
			}
		}
	}
}
void prefetchrrl(unsigned long int tagindex,unsigned long int setindex,int assoc)
{
	int i,j,min;
	for(i=0;i<assoc;i++)
	{
		if(cache[setindex][i].valid==0)
		{
			mr++;
			count++;
			cache[setindex][i].valid=1;
			cache[setindex][i].tag=tagindex;
			cache[setindex][i].time=count;
			return;
		}
		else
		{
			if(cache[setindex][i].tag==tagindex)
			{
				return;
			}
			if(i==(assoc-1))
			{
				mr++;
				min=0;
				for(j=0;j<assoc;j++)
				{
					if(cache[setindex][j].time<=cache[setindex][min].time)
					{
						min=j;
					}	
				}
			cache[setindex][min].valid=1;
	        	cache[setindex][min].tag=tagindex;
	        	count++;
	        	cache[setindex][min].time=count;
	    		return;
			}
		}
	}
}
	
void prefetchwl(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn)
{
	int i,j,min;
	for(i=0;i<assoc;i++)
	{
		if(cache[setindex][i].valid==0)
		{
			miss++;
			mr++;
			mw++;
			count++;
			cache[setindex][i].valid=1;
			cache[setindex][i].tag=tagindex;
			cache[setindex][i].time=count;
			prefetchww(tagindexn,setindexn,assoc);
			return;
		}
		else
		{
			if(cache[setindex][i].tag==tagindex)
			{
				hit++;
				mw++;
				count++;
				cache[setindex][i].time=count;
				return;
			}
			if(i==(assoc-1))
			{
				miss++;
				mr++;
				mw++;
				min=0;
				for(j=0;j<assoc;j++)
				{
					if(cache[setindex][j].time<=cache[setindex][min].time)
					{
						min=j;
					}	
				}
			cache[setindex][min].valid=1;
	        	cache[setindex][min].tag=tagindex;
	        	count++;
	        	cache[setindex][min].time=count;
	        	prefetchww(tagindexn, setindexn,assoc);
	        	return;
			}
		}
	}

}
void prefetchrl(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn)
{	
	int i,j,min;
	for(i=0;i<assoc;i++)
	{
		if(cache[setindex][i].valid==0)
		{
			miss++;
			mr++;
			count++;
			cache[setindex][i].valid=1;
			cache[setindex][i].tag=tagindex;
			cache[setindex][i].time=count;
			prefetchrr(tagindexn,setindexn,assoc);
			return;
		}
		else
		{
			if(cache[setindex][i].tag==tagindex)
			{
				hit++;
				count++;
				cache[setindex][i].time=count;
				return;
			}
			
			if(i==(assoc-1))
			{
				miss++;
				mr++;
				min=0;
				for(j=0;j<assoc;j++)
				{
				if(cache[setindex][j].time<=cache[setindex][min].time)
				{
				min=j;
				}	
			}
			cache[setindex][min].valid=1;
	        	cache[setindex][min].tag=tagindex;
	        	count++;
	        	cache[setindex][min].time=count;
	        	prefetchrr(tagindexn,setindexn,assoc);
			}
		}	
	}	
}
/* print helper */
void out(int isPrefetch)
{
	if(isPrefetch == 0)
	{
		printf("no-prefetch\n");	
	}
	else
	{
		printf("with-prefetch\n");
	}
	printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",mr,mw,hit,miss);
}
int main(int argc, char* argv[])
{
	// get args do check
	int cachesize=atoi(argv[1]);
  	int blocksize=atoi(argv[4]);
	if(blocksize > cachesize)
	{
		printf("error\n");
		return 0;
	}
  	int n, setnum, assoc, b, s;
  	char op;
  	unsigned long int address;
  	unsigned long int newaddress;
  	unsigned long int setmask;
  	unsigned long int tagindex;
  	unsigned long int setindex;
  	unsigned long int tagindexn;
  	unsigned long int setindexn;
  	FILE* f;
  	f=fopen(argv[5],"r");
	// np check
  	if(f==NULL)
	{
		printf("error\n");
    		return 0;
  	}
	// determine cache type, set vars accordingly
	if(argv[2][0]=='d')
	{
		assoc=1;
		setnum=cachesize/blocksize;
	}
	else if(argv[2][5]!=':')
	{
		setnum=1;
		assoc=cachesize/blocksize;
	}
	else
	{
    		sscanf(argv[2],"assoc:%d",&n);
    		assoc=n;
    		setnum=cachesize/blocksize/n;
  	}
	// get cache, mask 
	b=log(blocksize)/log(2);
	s=log(setnum)/log(2);
	setmask=((1<<s)-1);
	cache=getCache(setnum,assoc);
	// do non-prefetch simulation first, get set index, tag index, do operation
	while(fscanf(f, "%*x: %c %lx", &op, &address)==2)
	{
		setindex=(address>>b)&setmask;
		tagindex=address>>(b+s);
		// do operation
		if(op=='R')
		{
			doRead(tagindex,setindex,assoc);
		}
		else if(op=='W')
		{
			doWrite(tagindex,setindex,assoc);
		}
	}
	// reset file pointer, out vals, reset cache
	fclose(f);
	f=fopen(argv[5],"r");
	out(0); 
	resetCache(setnum,assoc);
	// now do prefetch simulation; get setindex, tag index and neighbor for prefetching
	while(fscanf(f, "%*x: %c %lx", &op, &address)==2)
	{
		setindex=(address>>b)&setmask;
		tagindex=address>>(b+s);
		newaddress=address+blocksize;
		setindexn=(newaddress>>b)&setmask;
		tagindexn=newaddress>>(b+s);
		// do operation
		if(op=='R')
		{
			prefetchrl(tagindex,setindex,assoc,tagindexn,setindexn);
		}
		else if(op=='W')
		{
			prefetchwl(tagindex,setindex,assoc,tagindexn,setindexn);
		}
	}	
	out(1);
	free(cache); 	
	
	return 0;
}

