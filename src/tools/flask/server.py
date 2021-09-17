from random import randrange

from flask.json import jsonify
from flask import Flask, render_template,request

from pyecharts import options as opts
from pyecharts.charts import Line,Bar,Grid
from pyecharts.options import series_options

from database import get_update_data,get_base_data,get_dbposition,get_profit

app = Flask(__name__, static_folder="templates")


def line_base(instrumentid) -> Grid:
    t,p,v=get_base_data(instrumentid)
    position=[get_dbposition(instrumentid) for i in range(len(t))]
    # t=[i for i in range(len(t))]
    line = (
        Line()
        .add_xaxis(t)
        .add_yaxis(
            series_name="",
            y_axis=p,
            is_smooth=False,
            label_opts=opts.LabelOpts(is_show=False),
        )
        .set_colors("blue")
        .set_global_opts(
            title_opts=opts.TitleOpts(title=instrumentid,pos_top="0%"),
            xaxis_opts=opts.AxisOpts(type_="time"),
            #yaxis_opts=opts.AxisOpts(type_="value",min_=p[0]-20),
            yaxis_opts=opts.AxisOpts(type_="value",min_="dataMin"),
        )
    )

    

    bar = (
        Bar()
        .add_xaxis([i for i in range(len(t))])
        .add_yaxis(series_name="", y_axis=v,label_opts=opts.LabelOpts(is_show=False),
                    itemstyle_opts=opts.ItemStyleOpts(color="green"))
        .set_global_opts(
            title_opts=opts.TitleOpts(title="volume",pos_top="30%"),
            xaxis_opts=opts.AxisOpts(type_="time",min_="dataMin"),
            yaxis_opts=opts.AxisOpts(type_="value",min_="dataMin"),
        )
    )

    line_pos = (
        Line()
        .add_xaxis([i for i in range(len(t))])
        .add_yaxis(series_name="",y_axis=position,is_smooth=False,label_opts=opts.LabelOpts(is_show=False),itemstyle_opts=opts.ItemStyleOpts(color="red"))
        .set_global_opts(
            title_opts=opts.TitleOpts(title="Position",pos_top="55%"),
            xaxis_opts=opts.AxisOpts(type_="time"),
            yaxis_opts=opts.AxisOpts(type_="value"),
        )
    )

    line_ret = (
        Line()
        .add_xaxis([i for i in range(len(t))])
        .add_yaxis(series_name="",y_axis=position,is_smooth=False,label_opts=opts.LabelOpts(is_show=False),itemstyle_opts=opts.ItemStyleOpts(color="red"))
        .set_global_opts(
            title_opts=opts.TitleOpts(title="Profit",pos_top="80%"),
            xaxis_opts=opts.AxisOpts(type_="time"),
            yaxis_opts=opts.AxisOpts(type_="value"),
        )
    )


    grid = (
        Grid()
        .add(line, grid_opts=opts.GridOpts(pos_top="5%",pos_bottom="75%"))
        .add(bar, grid_opts=opts.GridOpts(pos_top="35%",pos_bottom="50%"))
        .add(line_pos, grid_opts=opts.GridOpts(pos_top="60%",pos_bottom="30%"))
        .add(line_ret, grid_opts=opts.GridOpts(pos_top="80%",pos_bottom="0%"))
        # .render("grid_vertical.html")
    )



    return grid


@app.route("/")
def index():
    return render_template("index.html")

@app.route("/<name>")
def plot(name):
    print(name)
    return render_template("index.html",instrumentid=name)


@app.route("/lineChart/<instrumentid>")
def get_line_chart(instrumentid):
    print("instrument id 1 ",instrumentid)
    c = line_base(instrumentid)
    return c.dump_options_with_quotes()


idx = 19


@app.route("/lineDynamicData/<instrumentid>")
def update_line_data(instrumentid):
    global idx
    # instrumentid=request.args.get("instrumentid")
    idx=idx+1
    print("instrument id 2 ",instrumentid)
    t,p,v=get_update_data(instrumentid)
    print(t,p,v)

    position=str(get_dbposition(instrumentid))
    print("position is ",position)

    profit=get_profit(instrumentid)
    # return jsonify({"time": t, "value": p,"idx":idx,"volume":v})
    return jsonify({"time": t, "value": p,"volume":v,"position":position,"profit":profit})
    #return get_update_data("IF2109")



if __name__ == "__main__":
    #app.run()
    app.run(host="0.0.0.0",port=5001,debug=True)
