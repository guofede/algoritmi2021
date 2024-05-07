package graph;

import java.util.Collection;
import java.util.ArrayList;
import java.util.List;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

public class GraphTests{
	
	private Integer v1=1, v2=2, v3=3;
	private Integer t1=1, t2=2, t3=3;
	private Graph<Integer,Integer> graph;
	
	@Before
	public void CreateGraph() throws GraphException{
		graph = new Graph<>(Type.NON_DIRECTED);
	}
	
	@Test
	public void AddVertexTest()throws GraphException{
		graph.addVertex(v1);
		assertTrue(graph.containVertex(v1));
	}
	
	@Test
	public void AddMultipleVertexTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		assertTrue(graph.containVertex(v1) && graph.containVertex(v2) && graph.containVertex(v3));
	}
	
	@Test
	public void AddLinkTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addLink(v1,v2,t1);
		assertTrue(graph.containLink(v1,v2));
	}
	
	@Test
	public void RemoveVertexTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addLink(v1,v2,t1);
		graph.removeVertex(v1);
		assertFalse(graph.containVertex(v1) || graph.containLink(v2,v1));
	}
	
	@Test
	public void RemoveLinkTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addLink(v1,v2,t1);
		graph.removeLink(v1,v2);
		assertFalse(graph.containLink(v1,v2) || graph.containLink(v2,v1));
	}
	
	@Test
	public void ContainVertexTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		assertTrue(!graph.containVertex(v3) && graph.containVertex(v1) && graph.containVertex(v2));
	}
	
	@Test
	public void ContainLinkTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		graph.addLink(v1,v2, t2);
		assertTrue(graph.containLink(v1,v2) && graph.containLink(v2,v1) && !graph.containLink(v1,v3) && !graph.containLink(v3,v1));
	}
	
	@Test
	public void EmptyVertexSizeTest()throws GraphException{
		assertEquals(0, graph.vertexSize());
	}
	
	@Test
	public void VertexSizeTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		assertEquals(3,graph.vertexSize());
	}
	
	@Test
	public void EmptyLinkSizeTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		assertEquals(0,graph.linkSize());
	}
	
	@Test
	public void LinkSizeTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		graph.addLink(v1,v2,t1);
		graph.addLink(v2,v3,t2);
		graph.addLink(v1,v3,t3);
		assertEquals(3,graph.linkSize());
	}
	
	@Test
	public void EmptyGetVertexListTest()throws GraphException{
		List<Integer> vertexlist = graph.getVertexList();
		assertTrue(vertexlist.isEmpty());
	}
	
	@Test
	public void GetVertexListTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		List<Integer> vertexlist = graph.getVertexList();
		Collection<Integer> expected = new ArrayList<>();
		expected.add(v1);
		expected.add(v2);
		expected.add(v3);
		assertTrue(vertexlist.containsAll(expected));
	}
	
	@Test
	public void EmptyGetLinkListTest()throws GraphException{
		List<Triple<Integer,Integer>> linklist = graph.getLinkList();
		assertTrue(linklist.isEmpty());
	}
	
	@Test
	public void GetLinkListTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addLink(v1,v2,t1);
		List<Triple<Integer,Integer>> linklist = graph.getLinkList();
		assertEquals(2,linklist.size());
	}
	
	@Test
	public void EmptyGetAdjacentVertexTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		List<Integer> adjacentlist = graph.getAdjacentVertex(v1);
		assertTrue(adjacentlist.isEmpty());
	}
	
	@Test
	public void GetAdjacentVertexTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		graph.addLink(v1,v2,t1);
		graph.addLink(v2,v3,t2);
		graph.addLink(v1,v3,t3);
		List<Integer> adjacentlist = graph.getAdjacentVertex(v1);
		Collection<Integer> expected = new ArrayList<>();
		expected.add(v2);
		expected.add(v3);
		assertTrue(adjacentlist.containsAll(expected));
	}
	
	@Test
	public void NullGetTagTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		assertNull(graph.getTag(v1,v2));
	}
	
	@Test
	public void GetTagTest()throws GraphException{
		graph.addVertex(v1);
		graph.addVertex(v2);
		graph.addVertex(v3);
		graph.addLink(v1,v2,t1);
		assertEquals(t1,graph.getTag(v1,v2));
	}
}