import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-event-binding',
  template: `
  <h2>
    Welcome to {{eventBindingCompName}}
  </h2>
  <button (click)="onClick()">Greet</button> <!Button click example>
  {{greeting}} <!An example for an assignment while clicking at the button>
  <button (click)="onClickEvent($event)">Event</button> <!Event passing example>
  {{eventGreet}}
  <button (click)="noMethodGreet = 'No Method'">Click</button> <!No method example>
  {{noMethodGreet}}
  `,
  styles: []
})
export class EventBindingComponent implements OnInit {

  // Declaring the strings as "" and assign some string by a button click
  public eventBindingCompName = "EVENT-BINDING";
  public greeting = "";
  public eventGreet = "";
  public noMethodGreet = "";

  constructor() { }

  ngOnInit(): void {
  }

  onClick(){
    console.log('Welcome to Angular Tutor');
    this.greeting = "I appeared after the button was clicked";
  }

  onClickEvent(event){
    console.log(event);
    this.eventGreet = event.type;
  }
}
