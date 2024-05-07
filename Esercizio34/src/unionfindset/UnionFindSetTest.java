package unionfindset;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;

public class UnionFindSetTest{
	
	private UnionFindSet<Integer> set;
	private Integer i1,i2,i3;
	
	@Before
	public void createUnionFindSet()throws UnionFindSetException{
		set = new UnionFindSet<Integer>();
		i1 = 1;
		i2 = 2;
		i3 = 3;
		set.makeSet(i1);
		set.makeSet(i2);
		set.makeSet(i3);
	}
	
	@Test
	public void testFindSetRoot()throws UnionFindSetException{
		assertEquals(i1, set.findSet(i1));
	}
	
	@Test
	public void testFindSetGeneric() throws UnionFindSetException{
		set.union(i1,i2);
		set.union(i2,i3);
		assertEquals(i1, set.findSet(i3));
	}
	
	@Test
	public void testUnionSingle() throws UnionFindSetException{
		set.union(i1,i2);
		assertTrue(set.findSet(i1) == set.findSet(i2));
	}
	
	@Test
	public void testUnionGeneric() throws UnionFindSetException{
		set.union(i1,i2);
		set.union(i2,i3);
		assertTrue(set.findSet(i1) == set.findSet(i2));
	}
}