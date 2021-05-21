import { ComponentFixture, TestBed } from '@angular/core/testing';

import { HttpUsingComponent } from './http-using.component';

describe('HttpUsingComponent', () => {
  let component: HttpUsingComponent;
  let fixture: ComponentFixture<HttpUsingComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ HttpUsingComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(HttpUsingComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
