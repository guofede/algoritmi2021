package graph;

public class Triple<T,E>{
	private T from;
	private T to;
	private E tag;
	
	public Triple(T from, T to, E tag){
		this.from = from;
		this.to = to;
		this.tag = tag;
	}
	
	//from getter
	public T from(){
		return this.from;
	}
	//to getter
	public T to(){
		return this.to;
	}
	//tag getter
	public E tag(){
		return this.tag;
	}
}