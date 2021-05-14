import { Component, Input, Output, OnInit, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-component-interaction',
  template: `
  <h2>
    <br>
    Welcome to {{cIName}}
  </h2>

  <h2> {{"Hello " + parentData}} </h2>
  <button (click)="fireEvent()"> Send Event </button> 
`,
styles: []
})
export class ComponentInteractionComponent implements OnInit {

  public cIName = "COMPONENT-INTERACTION";

  // For Input and Output - look at the app.component.html file
  @Input() public parentData; // This line is equivalent to "@input('parentData') public varName;
  @Output() public childEvent = new EventEmitter();

  constructor() { }

  ngOnInit(): void {
  }

  fireEvent(){
    this.childEvent.emit('Got Output');
  }
}
