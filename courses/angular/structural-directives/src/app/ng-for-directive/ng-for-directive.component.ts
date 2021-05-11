import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-ng-for-directive',
  template: `
    <h2>
      Welcome to {{ngForName}}
    </h2>

    <h2>
      ----------
    </h2>

    <div *ngFor="let color of colors"> <! 'let' is used for var declaration in JS>
      <h2>{{color}}</h2>
    </div>

    <h2>
      ----------
    </h2>

    <div *ngFor="let color of colors; index as i"> 
      <h2>{{i}} {{color}}</h2> <! With indeces>
    </div>

    <h2>
      ----------
    </h2>

    <!---------- Conditional operations on list ---------->
    <div *ngFor="let color of colors; first as f"> 
      <h2>{{f}} {{color}}</h2> <! if FIRST>
    </div>

    <h2>
      ----------
    </h2>

    <div *ngFor="let color of colors; last as l"> 
      <h2>{{l}} {{color}}</h2> <! if LAST>
    </div>

    <h2>
      ----------
    </h2>

    <div *ngFor="let color of colors; odd as o"> 
      <h2>{{o}} {{color}}</h2> <! if ODD>
    </div>

    <h2>
      ----------
    </h2>

    <div *ngFor="let color of colors; even as e"> 
      <h2>{{e}} {{color}}</h2> <! if EVEN>
    </div>
  `,
  styles: []
})
export class NgForDirectiveComponent implements OnInit {

  public ngForName = "NG-FOR-DIRECTIVE";
  public colors = ["red", "green", "blue", "white"];

  constructor() { }

  ngOnInit(): void {
  }

}
