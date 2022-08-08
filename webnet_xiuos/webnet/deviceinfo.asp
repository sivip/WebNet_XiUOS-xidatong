<%@Language="vbscript" Codepage="65001"%>
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="xidatong webnet" />
    <meta name="author" content="gong" />
    <!-- <link rel="icon" href="../../favicon.ico" /> -->

    <title>xidatong web server set page</title>

    <script src="https://apps.bdimg.com/libs/jquery/2.1.4/jquery.min.js"></script>

    <script src="https://stackpath.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js" integrity="sha384-aJ21OjlMXNL5UyIl/XNwTMqvzeRMZH2w8c5cRVpzpU8Y5bApTppSuUkhZXN0VxHd" crossorigin="anonymous"></script>

    <!-- Bootstrap core CSS -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css" integrity="sha384-HSMxcRTRxnN+Bdg0JdbxYKrThecOKuH5zCYotlSAcp1+c8xmyTe9GYg1l9a69psu" crossorigin="anonymous">

    <!-- Custom styles for this template -->
    <link href="./css/layout.css" rel="stylesheet" />

    <style>
      .mt_15 {
        margin-top: 15vh;
      }
      .form-group {
        margin-bottom: 20px;
      }
    </style>
  </head>

  <body>
    <nav class="navbar navbar-inverse navbar-fixed-top">
      <div class="container-fluid">
        <div class="navbar-header">
          <button
            type="button"
            class="navbar-toggle collapsed"
            data-toggle="collapse"
            data-target="#navbar"
            aria-expanded="false"
            aria-controls="navbar"
            id="navbarToggle"
          >
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <img src="./logo/logo.png" height="50px" />
        </div>
        <div id="navbar" class="navbar-collapse collapse">
          <ul class="nav navbar-nav navbar-right">
            <li><a href="#"></a></li>
            <li><a href="#"></a></li>
            <li><a href="#"></a></li>
          </ul>
        </div>
        <!-- <div id="navbar" class="navbar-collapse collapse">
          <ul class="nav navbar-nav navbar-right">
            <li><a href="#">账号</a></li>
          </ul>
        </div> -->
      </div>
    </nav>

    <div class="container-fluid">
      <div class="row">
        <div class="col-sm-3 col-md-2 sidebar">
          <ul class="nav nav-sidebar">
            <li class="active">
              <a href="deviceinfo.asp">系统设置</a>
            </li>
            <li><a href="tcp.html">网络设置</a></li>
            <li><a href="chart.html">数据显示</a></li>
          </ul>
        </div>
        <div class="col-sm-9 col-sm-offset-3 col-md-10 col-md-offset-2 main">
          <h1 class="page-header">系统设置</h1>
          <ul class="nav nav-tabs card-header-tabs">
            <li role="presentation" class="active">
              <a href="deviceinfo.asp">系统信息</a>
            </li>
            <li role="presentation">
              <a href="systemModify.html">系统维护</a>
            </li>
          </ul>
          <div class="col-sm-8 col-sm-offset-3 mt_15">
            <form>
              <div class="form-group row">
                <label for="name" class="col-sm-3 col-xs-3 text-left"
                  >设备名称</label
                >
                <div class="col-sm-4">
                  <span class="form-control" id="name" disabled /><% device_name %>
                </div>
              </div>
              <div class="form-group row">
                <label for="no" class="col-sm-3 col-xs-3 text-left"
                  >设备编号</label
                >
                <div class="col-sm-4">
                  <span class="form-control" id="no" disabled /><% device_number %>
                </div>
              </div>
              <div class="form-group row">
                <label for="type" class="col-sm-3 col-xs-3 text-left"
                  >设备类型</label
                >
                <div class="col-sm-4">
                  <span class="form-control" id="type" disabled /><% device_type %>
                </div>
              </div>
              <div class="form-group row">
                <label for="seqNo" class="col-sm-3 col-xs-3 text-left"
                  >设备序列号</label
                >
                <div class="col-sm-4">
                  <span class="form-control" id="seqNo" disabled /><% device_serial %>
                </div>
              </div>
              <div class="form-group row">
                <label for="kernelType" class="col-sm-3 col-xs-3 text-left"
                  >内核类型</label
                >
                <div class="col-sm-4">
                  <span class="form-control" id="kernelType" disabled /><% os_type %>
                </div>
              </div>
              <div class="form-group row">
                <label for="webVersion" class="col-sm-3 col-xs-3 text-left"
                  >Web版本</label
                >
                <div class="col-sm-4">
                  <span class="form-control" id="webVersion" disabled /><% web_version %>
                </div>
              </div>
            </form>
          </div>
        </div>
      </div>
    </div>
  </body>
</html>
