// graph-tool -- a general graph modification and manipulation thingy
//
// Copyright (C) 2007  Tiago de Paula Peixoto <tiago@forked.de>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "graph_filtering.hh"

#include <boost/python.hpp>
#include <boost/lambda/bind.hpp>

#include "graph.hh"
#include "graph_selectors.hh"
#include "graph_eigentrust.hh"

using namespace std;
using namespace boost;
using namespace graph_tool;

size_t eigentrust(GraphInterface& g, boost::any c, boost::any t,
                  double epslon, size_t max_iter)
{
    if (!belongs<writable_edge_scalar_properties>()(c))
        throw GraphException("edge property must be writable");
    if (!belongs<vertex_floating_properties>()(t))
        throw GraphException("vertex property must be of floating point"
                             " value type");

    size_t iter = 0;
    run_action<>()
        (g, bind<void>
         (get_eigentrust(),
          _1, g.GetVertexIndex(), g.GetEdgeIndex(), _2,
          _3, epslon, max_iter, ref(iter)),
         writable_edge_scalar_properties(),
         vertex_floating_properties())(c,t);
    return iter;
}

void export_eigentrust()
{
    using namespace boost::python;
    def("get_eigentrust", &eigentrust);
}
