//
//  main.cpp
//  mapnik312_demo
//
//  Created by tomapto－lsg on 17/6/2.
//  Copyright © 2017年 tomapto－lsg. All rights reserved.
//

#include <mapnik/map.hpp>
#include <mapnik/layer.hpp>
#include <mapnik/rule.hpp>
#include <mapnik/feature_type_style.hpp>
#include <mapnik/symbolizer.hpp>
#include <mapnik/text/placements/dummy.hpp>
#include <mapnik/text/text_properties.hpp>
#include <mapnik/text/formatting/text.hpp>
#include <mapnik/datasource_cache.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/agg_renderer.hpp>
#include <mapnik/expression.hpp>
#include <mapnik/color_factory.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/unicode.hpp>
#include <mapnik/save_map.hpp>
#include <mapnik/cairo_io.hpp>
#include <mapnik/load_map.hpp>
#include <mapnik/projection.hpp>
#include <mapnik/proj_transform.hpp>

#if defined(HAVE_CAIRO)
#include <mapnik/cairo/cairo_renderer.hpp>
#include <mapnik/cairo/cairo_image_util.hpp>
#endif

#include <iostream>

using namespace mapnik;

int main(int, char**) {
    using namespace mapnik;
    datasource_cache::instance().register_datasources("/data/mapnik/release/lib/mapnik/input/");
    freetype_engine::register_font("/data/mapnik/release/lib/mapnik/fonts");

    Map m(800, 600);

    mapnik::load_map(m, "/data/mapnik/release/demo/map_world.xml", true);


    mapnik::box2d<double> input(116.3764853, 39.902910579, 116.414079141546, 39.9225291282612); //缩略图范围


//    projection prj_900913 = projection("+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +no_defs +over");
//    projection prj_4326 = projection("+proj=latlong +ellps=WGS84 +datum=WGS84 +no_defs");
//    proj_transform prj_trans(prj_4326, prj_900913);
//    prj_trans.forward(input);
    m.zoom_to_box(input);
    
    image_rgba8 buf(m.width(), m.height());
    agg_renderer<image_rgba8> ren(m, buf);
    ren.apply();
    save_to_file(buf,"demo.png","png");
}