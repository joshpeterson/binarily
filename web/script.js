function updateGUI(json, filePointer, fileSize) {
  var data = JSON.parse(json);
  var tableOfContents = document.getElementById("tableOfContents");
  removeChildren(tableOfContents);
  for (const section in data) {
    tableOfContents.appendChild(getTocRow(capitalize(section)));

    var mainContent = document.getElementById("mainContent");
    removeChildren(mainContent);
    mainContent.appendChild(getHeaderMainContent(data.header, section, true));

    var icon = document.getElementById("icon");
    removeChildren(icon);
    icon.appendChild(getFileTypeIcon(data.header, true));
  }
  var allDataName = "All data";
  tableOfContents.appendChild(getTocRow(allDataName));
  mainContent.appendChild(getAllDataMainContent(filePointer, fileSize, allDataName, false));
}

function removeChildren(element) {
  while (element.firstChild) {
        element.removeChild(element.firstChild);
  }
}

function hideChildren(element) {
  children = element.children;
  for (let i = 0; i < children.length; i++) {
        children[i].style.display = "none";
  }
}

function capitalize(s) {
  if (typeof s !== 'string') return ''
  return s.charAt(0).toUpperCase() + s.slice(1)
}

function getTocRow(text) {
  var div = document.createElement("div");
  div.setAttribute("class","row border p-1");
  div.appendChild(getToggleLink(text));
  return div;
}

function getToggleLink(text) {
  var a = document.createElement("a");
  a.setAttribute("href", "#");
  a.setAttribute("onclick", `showSection("${getId(text)}");`);
  a.innerText = capitalize(text);
  return a;
}

function getId(text) {
  return `${text.toLowerCase().replace(/ /g, '')}`;
}

function getPre(text, center) {
  var pre = document.createElement("pre");
  if (center)
    pre.setAttribute("class", "text-center");
  pre.innerText = text;
  return pre;
}

function getHeaderMainContent(header, id, display) {
    var text = "";
    text += formatHeaderLine("type", header);
    text += formatHeaderLine("bitness", header);
    text += formatHeaderLine("endianness", header);
    return getDiv(getPre(text, false), getId(id), display);
}

function formatHeaderLine(name, header) {
  if (name in header) {
    return capitalize(name) + ": " + header[name] + "\n";
  }
  return "";
}

function getFileTypeIcon(header) {
    if (header.type.includes("ELF"))
      return getLinuxIcon();
    return getUnknownIcon();
}

function getAllDataMainContent(filePointer, fileSize, id, display) {
  var text = formatFileData(filePointer, fileSize, 32);
  return getDiv(getPre(text, true), getId(id), display);
}

function formatFileData(filePointer, size, bytesPerRow) {
  var data = "";
  var i = 0;
  while (i < size) {
    data += "0x";
    var offset = "00000000" + i.toString(16);
    var offsetString = offset.slice(offset.length - 8) + " || ";
    data += offsetString;
    var ascii = "";

    for (var column = 0; column < bytesPerRow; column++) {
      var value = Module.HEAPU8[filePointer + i];
      ascii += formatAsciiForByte(value);
      var hex = value.toString(16).toUpperCase();
      if (hex.length == 1)
        hex = "0" + hex;
      data += hex;
      if (column < bytesPerRow - 1)
        data += " ";
      else
        data += " || " + ascii + "\n";


      if (((column+1) % 4 == 0) && column != bytesPerRow - 1)
        data += "| ";
      i++;
    }
  }

  return data;
}

function formatAsciiForByte(value) {
  if (value > 31 && value < 127)
    return String.fromCharCode(value);
  return ".";
}

function getLinuxIcon() {
  return getIcon("linux-brands.svg");
}

function getUnknownIcon() {
  return getIcon("question-circle-solid.svg");
}

function getIcon(fileName) {
  var img = document.createElement("img");
  img.setAttribute("src",fileName);
  img.setAttribute("id", "logo");
  img.setAttribute("alt", "File type logo");
  return img;
}

function wrapInDisplay1(element) {
  var h1 = document.createElement("h1");
  h1.setAttribute("class", "display-1")
  h1.appendChild(element);
  return h1;
}

function getDiv(childElement, id, display) {
  var div = document.createElement("div");
  div.setAttribute("id", id);
  div.appendChild(childElement);
  if (display) {
    div.style.display = "block";
  }
  else {
    div.style.display = "none";
  }
  return div;
}

function centerText(element) {
  var s = document.createElement("span");
  s.setAttribute("class", "text-center");
  s.appendChild(element);
  return s;
}

function showSection(id) {
  var mainContent = document.getElementById("mainContent");
  hideChildren(mainContent);

  var e = document.getElementById(id);
  if(e.style.display == 'block') {
      e.style.display = 'none';
  }
  else {
     e.style.display = 'block';
  }
}

function setupDragAndDrop() {
  // From https://www.smashingmagazine.com/2018/01/drag-drop-file-uploader-vanilla-js/
  let dropArea = document.getElementById('drop-area');

  ['dragenter', 'dragover', 'dragleave', 'drop'].forEach(eventName => {
    dropArea.addEventListener(eventName, preventDefaults, false)
  });

  ['dragenter', 'dragover'].forEach(eventName => {
    dropArea.addEventListener(eventName, highlight, false)
  });

  ['dragleave', 'drop'].forEach(eventName => {
    dropArea.addEventListener(eventName, unhighlight, false)
  });

  dropArea.addEventListener('drop', handleDrop, false);

  function highlight(e) {
    dropArea.classList.add('highlight')
  }

  function unhighlight(e) {
    dropArea.classList.remove('highlight')
  }

  function handleDrop(e) {
    inspectFile(e.dataTransfer);
  }

  function preventDefaults (e) {
    e.preventDefault();
    e.stopPropagation();
  }
}

function readFile(file) {
  return new Promise((resolve, reject) => {
    let fr = new FileReader();
    fr.onload = x=> resolve(fr.result);
    fr.readAsArrayBuffer(file);
})}

function enableFileInput() {
  document.getElementById("fileInput").disabled = false;
  document.getElementById("button").setAttribute("class", "btn-lg btn-primary");
  document.getElementById("dropText").setAttribute("class", "text-dark");
  setupDragAndDrop();
}

async function inspectFile(input) {
  var fileBuffer = await readFile(input.files[0]);
  const typedArray = new Uint8Array(fileBuffer);
  var heapSpace = Module._malloc(typedArray.length);
  Module.HEAPU8.set(typedArray, heapSpace);

  var fileData = Module.ccall('loadFileData', 'number', ['number', 'number'], [heapSpace, typedArray.length]);

  updateGUI(UTF8ToString(fileData), heapSpace, typedArray.length);

  Module._free(fileData);
}

// These function are useful for testing the GUI.

/*
function getTestJSON() {
  return '{"header":{"type":"ELF 64-bit Binary","bitness":"64-bit","endianness":"Unknown Endianness"}}';
}

window.onload = function() {
  updateGUI(getTestJSON());
  enableFileInput();
}
*/

